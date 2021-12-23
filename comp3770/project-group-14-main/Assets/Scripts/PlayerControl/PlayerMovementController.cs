using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
using TMPro;
using Mirror;

// Basic movememnt (no gravity, jumping, or running) based off of: https://www.youtube.com/watch?v=v8myO5BaZ-I
// https://www.youtube.com/watch?v=3N7_CY0d3Kk&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=14
public class PlayerMovementController : NetworkBehaviour
{
    [SerializeField] private float movementSpeed = 4.0f;
    [SerializeField] public int ammoAmt = 0, maxAmmo;
    [SerializeField] private CharacterController controller = null;
    [SerializeField] private GameObject playerUI = null, playerBody = null;
    [SerializeField] private TMP_Text deathText = null;
    [SerializeField] public TMP_Text blueScoreText = null, redScoreText = null, ammoText = null;
    [SerializeField] public Health health;

    private bool isRunning = false, isGrounded = true;
    public bool dead = false, holdingFlag = false;
    private Vector2 previousInput, playerVelocity;
    private Vector3 spawnPoint;
    private float gravityValue = -9.81f, jumpHeight = 1.0f, countdown = 5.0f;
    public string weapon;
    private int curBlueScore = 0, curRedScore = 0;

    public override void OnStartAuthority(){
        enabled = true;

        playerUI.SetActive(true);

        Cursor.lockState = CursorLockMode.Locked;
        spawnPoint = transform.position;

        // Assign max ammo
        if(weapon == "Magic"){
            maxAmmo = 20;
        }
        else if(weapon == "Gun"){
            maxAmmo = 25;
        }
        else if(weapon == "Sword"){
            maxAmmo = 20;
        }
        else if(weapon == "Spear"){
            maxAmmo = 10;
        }

        ammoAmt = maxAmmo;
        ammoText.text = "Ammo: " + ammoAmt;

        InputManager.Inputs.Player.Move.performed += ctx => SetMovement(ctx.ReadValue<Vector2>());
        InputManager.Inputs.Player.Move.canceled += ctx => ResetMovement();
        InputManager.Inputs.Player.Run.performed += ctx => PressSprint();
        InputManager.Inputs.Player.Run.canceled += ctx => PressSprint();
    }

    [ClientCallback]
    private void Update(){
        CmdUpdateScore();
        if(InputManager.Inputs.Player.Escape.triggered){
            Cursor.lockState = CursorLockMode.None;
        }

        if(!dead){
            Move();
        }
        else{
            countdown -= Time.deltaTime;
            deathText.text = "You are dead. Respawning in " + Mathf.Round(countdown) + " seconds.";
            if(countdown < 0){
                deathText.text = string.Empty;
                dead = !dead;
                health.currentHealth = 100;
                ammoAmt = maxAmmo;
                ammoText.text = "Ammo: " + ammoAmt;
                CmdSetHealth(health.currentHealth);
                countdown = 5.0f;
                
                // Tell server
                CmdSetStatus(dead);
                
                controller.enabled = true;
            }
        }
    }

    [Command]
    private void CmdUpdateScore(){
        if(curBlueScore != RoundSystem.score.blueScore || curRedScore != RoundSystem.score.redScore){
            curBlueScore = RoundSystem.score.blueScore;
            curRedScore = RoundSystem.score.redScore;
            RpcUpdateScore(curBlueScore, curRedScore);
        }
    }

    [ClientRpc]
    private void RpcUpdateScore(int newBlue, int newRed){
        curBlueScore = newBlue;
        curRedScore = newRed;
        blueScoreText.text = newBlue.ToString();
        redScoreText.text = newRed.ToString();
    }

    [Client]
    private void SetMovement(Vector2 movement) => previousInput = movement;

    [Client]
    private void ResetMovement() => previousInput = Vector2.zero;

    [ClientCallback]
    private void Move(){
        // Ground checks
        isGrounded = controller.isGrounded;

        if (isGrounded && playerVelocity.y < 0)
        {
            playerVelocity.y = 0f;
        }

        // Horizontal movement
        Vector3 right = controller.transform.right;
        Vector3 forward = controller.transform.forward;
        right.y = 0f;
        forward.y = 0f;

        if(isRunning){
            movementSpeed = 10.0f;
        }
        else{
            movementSpeed = 5.0f;
        }

        Vector3 movement = right.normalized * previousInput.x + forward.normalized * previousInput.y;
        controller.Move(movement * movementSpeed * Time.deltaTime);

        // Vertical movement
        if(InputManager.Inputs.Player.Jump.triggered && isGrounded){
            playerVelocity.y += Mathf.Sqrt(jumpHeight * -3.0f * gravityValue);
            AudioManager.jump.Play();
        }
        playerVelocity.y += gravityValue * Time.deltaTime;
        controller.Move(playerVelocity * Time.deltaTime);

        // Death related code
        if(transform.position.y < -10 || health.currentHealth == 0){
            AudioManager.fall.Play();
            CmdSetHealth(0);
            dead = !dead;

            // Tell server
            CmdSetStatus(dead);
            controller.enabled = false;
        }
    }

    [Command]
    public void CmdSetHealth(int value){
        health.SetHealth(value);
    }

    [Command]
    void CmdSetStatus(bool status){
        // Tell the server about a player's status
        if(status){
            playerBody.SetActive(false);
            transform.position = spawnPoint;
        }
        else if(!status){
            playerBody.SetActive(true);
        }

        // Tell the other clients
        RpcSetStatus(status);
    }

    [ClientRpc]
    void RpcSetStatus(bool status){
        // Tell other clients about a player's status
        if(status){
            playerBody.SetActive(false);
            transform.position = spawnPoint;
        }
        else if(!status){
            playerBody.SetActive(true);
        }        
    }
  
    // From A4, running feature based off of: https://www.youtube.com/watch?v=UqLl53ZPNfo
    [Client]
    private void PressSprint(){
        isRunning = !isRunning;
    }

    [ServerCallback]
    private void OnTriggerEnter(Collider other) {
        // If colliding with ammo pickup, add ammo
        if(other.gameObject.tag == "AmmoPickup"){
            AudioManager.pickupAmmo.Play();
        }
        
        // If colliding with a potion, increase health
        if(other.gameObject.tag == "Healing"){
            AudioManager.heal.Play();
        }

        // If colliding with projectiles, take damage
        if(other.gameObject.tag == "Projectile"){
            // Gun projectile
            if(other.gameObject.GetComponent<GunProjectile>() != null){
                // Extra check to prevent situation where player is running where the bullet spawned
                if(other.gameObject.GetComponent<GunProjectile>().shotBy != this){
                    health.currentHealth = Mathf.Max(health.currentHealth - 9, 0);
                    health.SetHealth(health.currentHealth);
                    AudioManager.damage.Play();
                    NetworkServer.Destroy(other.gameObject);
                }
            }
            // Magic projectile
            else if(other.gameObject.GetComponent<WandProjectile>() != null){
                // Extra check to prevent situation where player is running where the bullet spawned
                if(other.gameObject.GetComponent<WandProjectile>().shotBy != this){
                    health.currentHealth = Mathf.Max(health.currentHealth - 10, 0);
                    health.SetHealth(health.currentHealth);
                    AudioManager.damage.Play();
                    NetworkServer.Destroy(other.gameObject);
                }
            }

            // Sword projectile
             else if(other.gameObject.GetComponent<SwordSpiritProjectile>() != null){
                // Extra check to prevent situation where player is running where the bullet spawned
                if(other.gameObject.GetComponent<SwordSpiritProjectile>().shotBy != this){
                    health.currentHealth = Mathf.Max(health.currentHealth - 10, 0);
                    health.SetHealth(health.currentHealth);
                    AudioManager.damage.Play();
                    NetworkServer.Destroy(other.gameObject);
                }
            }

            // Spear projectile
               else if(other.gameObject.GetComponent<laserProjectile>() != null){
                // Extra check to prevent situation where player is running where the bullet spawned
                if(other.gameObject.GetComponent<laserProjectile>().shotBy != this){
                    health.currentHealth = Mathf.Max(health.currentHealth - 9, 0);
                    health.SetHealth(health.currentHealth);
                    AudioManager.damage.Play();
                    NetworkServer.Destroy(other.gameObject);
                }
            }



        }
    }
}
