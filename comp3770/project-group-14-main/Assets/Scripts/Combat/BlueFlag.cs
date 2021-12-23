using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;

public class BlueFlag : NetworkBehaviour
{
    [SyncVar]
    public bool flagActive = true;
    [SerializeField]
    private GameObject flagBody = null;
    private PlayerMovementController tookByPlayer = null;

    // Update is called once per frame
    [ServerCallback]
    private void Update(){
        if(tookByPlayer != null){
            if(!flagActive && (tookByPlayer.dead || !tookByPlayer.holdingFlag)){
                flagActive = !flagActive;
                tookByPlayer.holdingFlag = false;
                tookByPlayer = null;
                flagBody.SetActive(flagActive);
                // Tell other clients
                RpcChangeState(flagActive);            
            }
        }
    }

    [ServerCallback]
    private void OnTriggerEnter(Collider other){
        // Red player captures blue flag
        if(other.gameObject.tag == "RedPlayer"){
            if(flagActive){
                AudioManager.takeFlag.Play();
                flagActive = !flagActive;
                flagBody.SetActive(flagActive);
                tookByPlayer = other.transform.root.gameObject.GetComponent<PlayerMovementController>();
                tookByPlayer.holdingFlag = true;
                // Tell other clients
                RpcChangeState(flagActive);
            }
        }
        // Blue player returns red flag to base
        if(other.gameObject.tag == "BluePlayer"){
            PlayerMovementController collidedPlayer = other.transform.root.gameObject.GetComponent<PlayerMovementController>();
            if(collidedPlayer.holdingFlag){
                AudioManager.captureFlag.Play();
                RoundSystem.score.blueScore++;
                collidedPlayer.holdingFlag = false;
            }
        }
    }

    [ClientRpc]
    public void RpcChangeState(bool state){
        flagActive = state;
        flagBody.SetActive(state);
    }
}
