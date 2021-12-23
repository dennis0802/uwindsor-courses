using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;

// Based off of: https://www.youtube.com/watch?v=8n38L-7aFPY&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=14
// Store all maps (scenes) in one asset

[CreateAssetMenu(fileName = "New Map Set", menuName = "Maps/Map Set")]
public class MapSet : ScriptableObject{
    [Scene]
    [SerializeField] private List<string> maps = new List<string>();

    public IReadOnlyCollection<string> Maps => maps.AsReadOnly();
}
