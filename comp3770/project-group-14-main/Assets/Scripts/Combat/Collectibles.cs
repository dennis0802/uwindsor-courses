using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;

public class Collectibles : NetworkBehaviour
{
    [SyncVar]
    public bool isActive = true;
    [SerializeField]
    private GameObject pickupBody = null;
    private float countdown = 15.0f;

    [ServerCallback]
    private void Update(){
        // Respawning item process
        if(!isActive){
            countdown -= Time.deltaTime;
            //Debug.Log(countdown);
            if(countdown <= 0){
                pickupBody.SetActive(true);
                countdown = 15.0f;

                // Tell the clients
                RpcChangeState(true);
            }
        }
    }

    [ServerCallback]
    private void OnTriggerEnter(Collider other) {
        if(other.gameObject.tag == "BluePlayer" || other.gameObject.tag == "RedPlayer"){
            PlayerMovementController player = other.transform.root.gameObject.GetComponent<PlayerMovementController>();

            // Pick up ammo
            if(gameObject.tag == "AmmoPickup"){
                // Apply to relevant client
                TargetAmmo(other.gameObject.transform.root.gameObject.GetComponent<NetworkIdentity>().connectionToClient, player);
                pickupBody.SetActive(false);
                isActive = !isActive;
                RpcChangeState(isActive);
            }
            // Healing
            else if(gameObject.tag == "Healing"){
                // Apply to relevant client
                TargetHeal(other.gameObject.transform.root.gameObject.GetComponent<NetworkIdentity>().connectionToClient, player);
                pickupBody.SetActive(false);
                isActive = !isActive;
                RpcChangeState(isActive);
            }
        }
    }

    // To certain clients
    [TargetRpc]
    private void TargetHeal(NetworkConnection conn, PlayerMovementController player){
        player.health.currentHealth = Mathf.Min(player.health.currentHealth + 20, 100);
        player.CmdSetHealth(player.health.currentHealth);
    }

    [TargetRpc]
    private void TargetAmmo(NetworkConnection conn, PlayerMovementController player){
        player.ammoAmt = Mathf.Min(player.ammoAmt + 10, player.maxAmmo);
        player.ammoText.text = "Ammo: " + player.ammoAmt;
    }

    // To all clients
    [ClientRpc]
    private void RpcChangeState(bool state){
        isActive = state;
        pickupBody.SetActive(state);
    }
}
