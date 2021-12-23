using System.Collections;
using System.Collections.Generic;
using UnityEngine.InputSystem;
using UnityEngine;
using Cinemachine;

public class SwitchCameras : MonoBehaviour
{
    // Based off of: https://www.youtube.com/watch?v=SeBEvM2zMpY
    [SerializeField]
    private PlayerInput playerInput;
    [SerializeField]
    private int priorityBoost = 10;
    private CinemachineVirtualCamera virtualCamera;
    private InputAction switchAction;
    private bool isSwitched = false;
    [SerializeField]
    private Canvas firstPerson, thirdPerson;

    // Start is called before the first frame update
    void Start()
    {

    }

    void Awake(){
        virtualCamera = GetComponent<CinemachineVirtualCamera>();
        switchAction = playerInput.actions["Switch"];
    }

    void Update(){
        // Switching first person and third person cameras
        if(switchAction.triggered){
            AudioManager.buttonClick.Play();
            if(isSwitched){
                isSwitched = false;
                CancelFirstPerson();
            }
            else if(!isSwitched){
                isSwitched = true;
                StartFirstPerson();
            }
        }
    }

    // Change priority depending on whether switch key is held
    void StartFirstPerson(){
        firstPerson.enabled = true;
        thirdPerson.enabled = false;
        virtualCamera.Priority += priorityBoost;
    }

    void CancelFirstPerson(){
        firstPerson.enabled = false;
        thirdPerson.enabled = true;
        virtualCamera.Priority -= priorityBoost;
    }
}
