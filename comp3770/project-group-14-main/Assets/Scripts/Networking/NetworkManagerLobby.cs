using Mirror;
using System;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;
using System.Collections.Generic;

// Based off of: https://www.youtube.com/watch?v=Fx8efi2MNz0
//               https://www.youtube.com/watch?v=WMJS7sVp2FQ
//               https://www.youtube.com/watch?v=n_W4F5NckCA&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=7
//               https://www.youtube.com/watch?v=s2ypWi553nY&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=8
//               https://www.youtube.com/watch?v=kGikwYSBpZA&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=13
//               https://www.youtube.com/watch?v=8n38L-7aFPY&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=14

public class NetworkManagerLobby : NetworkManager {
    [SerializeField] private int minPlayers = 4;
    [Scene][SerializeField] private string menuScene = string.Empty;

    [Header("Maps")]
    [SerializeField] private int numberOfRounds = 3;
    [SerializeField] private MapSet mapSet = null;

    [Header("Room")]
    [SerializeField] private NetworkRoomPlayerLobby roomPlayerPrefab = null;

    [Header("Game")]
    [SerializeField] private NetworkGamePlayerLobby gamePlayerPrefab = null;
    [SerializeField] private GameObject playerSpawnSystem = null;
    [SerializeField] private GameObject roundSystem = null;

    private MapHandler mapHandler;

    public static NetworkManagerLobby instance;

    public static event Action OnClientConnected;
    public static event Action OnClientDisconnected;
    public static event Action<NetworkConnection> OnServerReadied;
    public static event Action OnServerStopped;

    public List<NetworkRoomPlayerLobby> RoomPlayers {get;} = new List<NetworkRoomPlayerLobby>();
    public List<NetworkGamePlayerLobby> GamePlayers {get;} = new List<NetworkGamePlayerLobby>();
    public List<NetworkRoomPlayerLobby> BluePlayers {get;} = new List<NetworkRoomPlayerLobby>();
    public List<NetworkRoomPlayerLobby> RedPlayers {get;} = new List<NetworkRoomPlayerLobby>();

    // Check for an existing NetworkManager
    public override void Awake(){
        if(instance == null){
            instance = this;
            DontDestroyOnLoad(gameObject);
        }
        else if(instance != this){
            Destroy(gameObject);
        }
        base.Awake();
    }

    public override void OnStartServer(){
        spawnPrefabs.Clear();
        spawnPrefabs = Resources.LoadAll<GameObject>("SpawnablePrefabs").ToList();
    }

    // Client functions - starting, connecting, disconnecting
    public override void OnStartClient(){
        spawnPrefabs.Clear();
        var spawnablePrefabs = Resources.LoadAll<GameObject>("SpawnablePrefabs");

        NetworkClient.ClearSpawners();
        foreach (var prefab in spawnablePrefabs){
            NetworkClient.RegisterPrefab(prefab);
        }
    }

    public override void OnClientConnect(NetworkConnection conn){
        base.OnClientConnect(conn);
        OnClientConnected?.Invoke();
    }

    public override void OnClientDisconnect(NetworkConnection conn){
        base.OnClientDisconnect(conn);
        OnClientDisconnected?.Invoke();
    }

    // Server functions - connecting, adding, disconencting
    public override void OnServerConnect(NetworkConnection conn){
        // Stop if too many players
        if(numPlayers >= maxConnections){
            conn.Disconnect();
            return;
        }
        // Prevent joining if in game
        if(SceneManager.GetActiveScene().path != menuScene){
            NetworkRoomPlayerLobby roomPlayerInstance = Instantiate(roomPlayerPrefab);
        }
    }

    // Add a new player to the server
    public override void OnServerAddPlayer(NetworkConnection conn){
        if(SceneManager.GetActiveScene().path == menuScene){
            bool isLeader = RoomPlayers.Count == 0;
            NetworkRoomPlayerLobby roomPlayerInstance = Instantiate(roomPlayerPrefab);
            roomPlayerInstance.IsLeader = isLeader;
            NetworkServer.AddPlayerForConnection(conn, roomPlayerInstance.gameObject);
        }
    }

    // Remove the player who left and change related statuses
    public override void OnServerDisconnect(NetworkConnection conn){
        if(conn.identity != null){
            var player = conn.identity.GetComponent<NetworkRoomPlayerLobby>();
            RoomPlayers.Remove(player);
            NotifyPlayersOfReadyState();
        }

        base.OnServerDisconnect(conn);
    }

    // Clear the lists when stopping server
    public override void OnStopServer(){
        OnServerStopped?.Invoke();

        RoomPlayers.Clear();
        GamePlayers.Clear();
        RedPlayers.Clear();
        BluePlayers.Clear();
    }

    // Notify players of ready status
    public void NotifyPlayersOfReadyState(){
        foreach(var player in RoomPlayers){
            player.HandleReadyToStart(IsReadyToStart());
        }
    }

    // Check if insufficient players and ready statuses
    private bool IsReadyToStart(){
        // Player count check
        if(numPlayers < minPlayers){
            Debug.Log("Not enough players");
            return false;
        }

        // Ready status check
        foreach(var player in RoomPlayers){
            if(!player.IsReady){
                Debug.Log("Not everyone is ready");
                return false;
            }
        }

        // Team count check
        if(BluePlayers.Count() != 2 && RedPlayers.Count() != 2){
            Debug.Log("The teams are unequal and/or don't have 2 members");
            return false;
        }

        return true;
    }

    // Start game
    public void StartGame(){
        if(SceneManager.GetActiveScene().path == menuScene){
            if(!IsReadyToStart()){
                return;
            }
            mapHandler = new MapHandler(mapSet, numberOfRounds);
            ServerChangeScene(mapHandler.NextMap);
        }
    }

    public void StopBGM(){
        AudioManager.bgm.Stop();
    }

    // Go to next map until all maps have been played
    public void GoToNextMap(){
        if(mapHandler.IsComplete){
            // Host (server+client)
            if(NetworkServer.active && NetworkClient.isConnected){
                NetworkManagerLobby.singleton.StopHost();
            }
            // Client
            else if(NetworkClient.isConnected){
                NetworkManagerLobby.singleton.StopClient();
            }
            // Server-only
            else if(NetworkServer.active){
                NetworkManagerLobby.singleton.StopServer();
            }
            return;
        }
        ServerChangeScene(mapHandler.NextMap);
    }

    // Changing scenes
    public override void ServerChangeScene(string newSceneName){
        // Menu to game
        if(SceneManager.GetActiveScene().path == menuScene && newSceneName.StartsWith("Assets/Scenes/Arena")){
            for(int i = RoomPlayers.Count - 1; i >= 0; i--){
                var conn = RoomPlayers[i].connectionToClient;
                var gamePlayerInstance = Instantiate(gamePlayerPrefab);
                gamePlayerInstance.SetDisplayName(RoomPlayers[i].DisplayName);
                gamePlayerInstance.SetTeam(RoomPlayers[i].Team);
                gamePlayerInstance.SetWeapon(RoomPlayers[i].Weapon);

                NetworkServer.ReplacePlayerForConnection(conn, gamePlayerInstance.gameObject);
            }
        }

        base.ServerChangeScene(newSceneName);
    }

    // Changing scnenes
    public override void OnServerSceneChanged(string sceneName){
        if(sceneName.StartsWith("Assets/Scenes/Arena")){
            GameObject playerSpawnSystemInstance = Instantiate(playerSpawnSystem);
            NetworkServer.Spawn(playerSpawnSystemInstance);

            GameObject roundSystemInstance = Instantiate(roundSystem);
            NetworkServer.Spawn(roundSystemInstance);
        }
    }

    // When server is ready
    public override void OnServerReady(NetworkConnection conn){
        base.OnServerReady(conn);

        OnServerReadied?.Invoke(conn);
    }
}