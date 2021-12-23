using UnityEngine;

// Based off of: https://www.youtube.com/watch?v=s2ypWi553nY&t=1s
public class PlayerSpawnPoint : MonoBehaviour{
    private void Awake() => PlayerSpawnSystem.AddSpawnPoint(gameObject);
    private void OnDestroy() => PlayerSpawnSystem.RemoveSpawnPoint(gameObject);

    // Visualization of spawn point
    // Red = red team, Blue = blue team, White = unassigned
    private void OnDrawGizmos() {
        if(gameObject.tag == "BlueSpawn"){
            Gizmos.color = Color.blue;
        }
        else if(gameObject.tag == "RedSpawn"){
            Gizmos.color = Color.red;
        }
        else{
            Gizmos.color = Color.white;
        }
        Gizmos.DrawSphere(transform.position, 1f);
        Gizmos.color = Color.green;
        Gizmos.DrawLine(transform.position, transform.position + transform.forward * 2);
    }
}