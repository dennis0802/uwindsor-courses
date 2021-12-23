using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Based off of: https://www.youtube.com/watch?v=3N7_CY0d3Kk&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=14
// All input will be handled from here rather than the player's movement scripts
public class InputManager : MonoBehaviour
{
    private static readonly IDictionary<string, int> mapStates = new Dictionary<string, int>();

    private static Input inputs;
    public static Input Inputs{
        get{
            if(inputs != null){
                return inputs;
            }
            return inputs = new Input();
        }
    }

    private void Awake(){
        if(inputs != null){
            return;
        }
        inputs = new Input();
    }

    private void OnEnable() => Inputs.Enable();
    private void OnDisable() => Inputs.Disable();
    private void OnDestroy() => inputs = null;

    public static void Add(string mapName){
        mapStates.TryGetValue(mapName, out int value);
        mapStates[mapName] = value + 1;

        UpdateMapState(mapName);
    }

    public static void Remove(string mapName){
        mapStates.TryGetValue(mapName, out int value);
        mapStates[mapName] = Mathf.Max(value - 1, 0);

        UpdateMapState(mapName);
    }

    private static void UpdateMapState(string mapName){
        int value = mapStates[mapName];

        if(value > 0){
            Inputs.asset.FindActionMap(mapName).Disable();
            return;
        }

        Inputs.asset.FindActionMap(mapName).Enable();
    }
}
