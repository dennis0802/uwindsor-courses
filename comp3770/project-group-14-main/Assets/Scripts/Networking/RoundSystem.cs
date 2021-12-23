using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using Mirror;

// Based off of: https://www.youtube.com/watch?v=kGikwYSBpZA&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=13
//               https://www.youtube.com/watch?v=3N7_CY0d3Kk&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=14
public class RoundSystem : NetworkBehaviour{
    [SerializeField] private Animator animator = null;
    public static Score score;

    private NetworkManagerLobby room;
    private NetworkManagerLobby Room{
        get{
            if(room != null){
                return room;
            }
            return room = NetworkManager.singleton as NetworkManagerLobby;
        }
    }

    public void CountdownEnded(){
        animator.enabled = false;
    }

    public override void OnStartServer(){
        NetworkManagerLobby.OnServerStopped += CleanUpServer;
        NetworkManagerLobby.OnServerReadied += CheckToStartRound;
        score = GetComponent<Score>();
    }

    [ServerCallback]
    private void OnDestroy() => CleanUpServer();

    [Server]
    private void CleanUpServer(){
        NetworkManagerLobby.OnServerStopped -= CleanUpServer;
        NetworkManagerLobby.OnServerReadied -= CheckToStartRound;
    }

    [ServerCallback]
    public void StartRound(){
        RpcStartRound();
    }

    // Check if ok to start the round - everyone should be connected
    [Server]
    private void CheckToStartRound(NetworkConnection conn){
        if(Room.GamePlayers.Count(x => x.connectionToClient.isReady) != Room.GamePlayers.Count){
            return;
        }
        animator.enabled = true;

        RpcStartCountdown();
    }

    // Begin countdown to start for all clients
    [ClientRpc]
    private void RpcStartCountdown(){
        animator.enabled = true;
    }

    // Temporarily disable input before the round officially starts
    [ClientRpc]
    private void RpcStartRound(){
        InputManager.Remove(ActionMapNames.Player);
    }

    // Handle points in a match
    [ServerCallback]
    private void Update(){
        if(score.blueScore == 10){
            HandleRoundEnd();
            score.blueScore = 0;
            score.redScore = 0;
        }
        else if(score.redScore == 10){
            HandleRoundEnd();
            score.blueScore = 0;
            score.redScore = 0;
        }
    }

    // Move to next map when round ends
    [Server]
    private void HandleRoundEnd(){
        Room.GoToNextMap();
    }
}
