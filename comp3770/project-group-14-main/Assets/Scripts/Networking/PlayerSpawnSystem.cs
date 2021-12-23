using Mirror;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

// Based off of: https://www.youtube.com/watch?v=s2ypWi553nY&t=1s
//               https://www.youtube.com/watch?v=3N7_CY0d3Kk&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=14
public class PlayerSpawnSystem : NetworkBehaviour{
    [SerializeField] 
    private GameObject blueGun, blueSword, blueSpear, blueMagic, redGun, redSword, redSpear, redMagic;

    private static List<Transform> redSpawns = new List<Transform>();
    private static List<Transform> blueSpawns = new List<Transform>();
    private int nextBlueIndex = 0, nextRedIndex = 0;

    // Add spawnpoints depending on tag attached to the spawnpoint.
    public static void AddSpawnPoint(GameObject spawn){
        if(spawn.tag == "BlueSpawn"){
            blueSpawns.Add(spawn.transform);
            blueSpawns = blueSpawns.OrderBy(x => x.GetSiblingIndex()).ToList();
        }
        else if(spawn.tag == "RedSpawn"){
            redSpawns.Add(spawn.transform);
            redSpawns = redSpawns.OrderBy(x => x.GetSiblingIndex()).ToList();
        }
        else{
            Debug.LogError($"Invalid spawnpoint. Assign a team tag to the spawnpoint");
        }
    }

    // Remove spawnpoints depending on tag attached to the spawnpoint.
    public static void RemoveSpawnPoint(GameObject spawn){
        if(spawn.tag == "BlueSpawn"){
            blueSpawns.Remove(spawn.transform);
        }
        else if(spawn.tag == "RedSpawn"){
            redSpawns.Remove(spawn.transform);
        }
        else{
            Debug.LogError($"Invalid spawnpoint. Assign a team tag to the spawnpoint");
        }        
    }

    public override void OnStartServer() => NetworkManagerLobby.OnServerReadied += SpawnPlayer;
    public override void OnStartClient(){
        InputManager.Add(ActionMapNames.Player);
        InputManager.Inputs.Player.Look.Enable();
    }

    [ServerCallback]
    private void OnDestroy() => NetworkManagerLobby.OnServerReadied -= SpawnPlayer;

    [Server]
    public void SpawnPlayer(NetworkConnection conn){
        Transform blueSpawn = blueSpawns.ElementAtOrDefault(nextBlueIndex);
        Transform redSpawn = redSpawns.ElementAtOrDefault(nextRedIndex);
        GameObject playerInstance = null;

        // Determine which connection
        NetworkGamePlayerLobby instance = conn.identity.gameObject.GetComponent<NetworkGamePlayerLobby>();

        // Decide which model to spawn (team and weapon dependent)
        if(instance.Team == "Blue"){
            if(blueSpawn == null){
                Debug.LogError($"Missing spawn point for blue player {nextBlueIndex}");
                return;
            }

            if(instance.Weapon == "Gun"){
                playerInstance = Instantiate(blueGun, blueSpawns[nextBlueIndex].position, blueSpawns[nextBlueIndex].rotation);
                playerInstance.GetComponent<PlayerMovementController>().weapon = "Gun";
            }
            else if(instance.Weapon == "Sword"){
                playerInstance = Instantiate(blueSword, blueSpawns[nextBlueIndex].position, blueSpawns[nextBlueIndex].rotation);
                playerInstance.GetComponent<PlayerMovementController>().weapon = "Sword";               
            }
            else if(instance.Weapon == "Spear"){
                playerInstance = Instantiate(blueSpear, blueSpawns[nextBlueIndex].position, blueSpawns[nextBlueIndex].rotation);
                playerInstance.GetComponent<PlayerMovementController>().weapon = "Spear";               
            }
            else if(instance.Weapon == "Magic"){
                playerInstance = Instantiate(blueMagic, blueSpawns[nextBlueIndex].position, blueSpawns[nextBlueIndex].rotation); 
                playerInstance.GetComponent<PlayerMovementController>().weapon = "Magic";              
            }
            else{
                Debug.LogError($"Missing weapon for blue player {nextBlueIndex}");
                return;           
            }
            nextBlueIndex++; 
        }
        else if(instance.Team == "Red"){
            if(redSpawn == null){
                Debug.LogError($"Missing spawn point for red player {nextRedIndex}");
                return;           
            }

            if(instance.Weapon == "Gun"){
                playerInstance = Instantiate(redGun, redSpawns[nextRedIndex].position, redSpawns[nextRedIndex].rotation);
                playerInstance.GetComponent<PlayerMovementController>().weapon = "Gun";
            }
            else if(instance.Weapon == "Sword"){
                playerInstance = Instantiate(redSword, redSpawns[nextRedIndex].position, redSpawns[nextRedIndex].rotation);
                playerInstance.GetComponent<PlayerMovementController>().weapon = "Sword";
            }
            else if(instance.Weapon == "Spear"){
                playerInstance = Instantiate(redSpear, redSpawns[nextRedIndex].position, redSpawns[nextRedIndex].rotation);
                playerInstance.GetComponent<PlayerMovementController>().weapon = "Spear";
            }
            else if(instance.Weapon == "Magic"){
                playerInstance = Instantiate(redMagic, redSpawns[nextRedIndex].position, redSpawns[nextRedIndex].rotation);
                playerInstance.GetComponent<PlayerMovementController>().weapon = "Magic";
            }
            else{
                Debug.LogError($"Missing weapon for red player {nextRedIndex}");
                return;           
            }
            nextRedIndex++;
        }
        
        NetworkServer.Spawn(playerInstance, conn);
    }
}