using UnityEngine;
using Mirror;
using Cinemachine;

// Based off of: https://www.youtube.com/watch?v=B4vNWUTQues
public class PlayerCameraController : NetworkBehaviour
{
    [Header("Camera")]
    [SerializeField] private Vector2 maxFollowOffset = new Vector2(-1f, 6f);
    [SerializeField] private Vector2 cameraVelocity = new Vector2(4f, 0.25f);
    [SerializeField] private Transform playerTransform = null;
    [SerializeField] private CinemachineVirtualCamera virtualCamera = null;

    private Input controls;
    private Input Controls{
        get{
            if(controls != null){
                return controls;
            }
            return controls = new Input();
        }
    }
    private CinemachineTransposer transposer;

    public override void OnStartAuthority(){
        transposer = virtualCamera.GetCinemachineComponent<CinemachineTransposer>();
        virtualCamera.gameObject.SetActive(true);
        enabled = true;

        Controls.Player.Look.performed += ctx => Look(ctx.ReadValue<Vector2>());
    }

    [ClientCallback]
    private void OnEnable() => Controls.Enable();
    [ClientCallback]
    private void OnDisable() => Controls.Disable();

    // Follow where player looks
    private void Look(Vector2 lookAxis){
        // Checking this will prevent errors when the client is sent back to the menu
        if(!(this == null)){
            float deltaTime = Time.deltaTime;

            float followOffest = Mathf.Clamp(transposer.m_FollowOffset.y - (lookAxis.y * cameraVelocity.y * deltaTime), maxFollowOffset.x, 
                                maxFollowOffset.y);
            
            transposer.m_FollowOffset.y = followOffest;

            playerTransform.Rotate(0f, lookAxis.x * cameraVelocity.x * deltaTime, 0f);
        }
    }

}
