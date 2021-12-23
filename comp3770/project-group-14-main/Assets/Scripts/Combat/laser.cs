using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;

// Based off of Mirror's Tanks example

public class laser : NetworkBehaviour
{
    [SerializeField] private GameObject laserPrefab;
    [SerializeField] private GameObject Laser;
    [SerializeField] private GameObject player;
    private PlayerMovementController playerScript;

    private void Start(){
        playerScript = player.GetComponent<PlayerMovementController>();
    }

    [ClientCallback]
    private void Update(){
        if(!hasAuthority){
            return;
        }
        if(!InputManager.Inputs.Player.Attack.triggered){
             return;
        }
        if(!playerScript.dead){
            Shoot();
        }
    }

    // Shooting code
    [ClientCallback]
    private void Shoot(){
        if(Cursor.lockState != CursorLockMode.Locked){
            Cursor.lockState = CursorLockMode.Locked;
        }

        if(playerScript.ammoAmt > 0){
            AudioManager.lasershoot.Play();
            CmdShoot();

            playerScript.ammoAmt--;
            playerScript.ammoText.text = "Ammo: " + playerScript.ammoAmt;
        }
    }

    // Spawn the bullet on the network - for all clients
    [Command]
    private void CmdShoot(){
        GameObject laser = GameObject.Instantiate(laserPrefab, Laser.transform.position, transform.rotation);
        laser.GetComponent<laserProjectile>().shotBy = gameObject.transform.root.GetComponent<PlayerMovementController>();
        NetworkServer.Spawn(laser);
    }
}