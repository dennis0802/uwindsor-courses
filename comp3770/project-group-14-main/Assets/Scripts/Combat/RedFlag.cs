using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;

public class RedFlag : NetworkBehaviour
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
                RpcChangeState(flagActive);            
            }
        }
    }

    [ServerCallback]
    private void OnTriggerEnter(Collider other){
        // Blue player captures red flag
        if(other.gameObject.tag == "BluePlayer"){
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

        // Red player returns blue flag to base
        if(other.gameObject.tag == "RedPlayer"){
            PlayerMovementController collidedPlayer = other.transform.root.gameObject.GetComponent<PlayerMovementController>();
            if(collidedPlayer.holdingFlag){
                AudioManager.captureFlag.Play();
                RoundSystem.score.redScore++;
                collidedPlayer.holdingFlag = false;
            }
        }
    }

    [ClientRpc]
    private void RpcChangeState(bool state){
        flagActive = state;
        flagBody.SetActive(state);
    }
}
