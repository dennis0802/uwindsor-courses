using System.Collections;
using System.Collections.Generic;
using System.Linq;

// Based off of: https://www.youtube.com/watch?v=8n38L-7aFPY&list=PLS6sInD7ThM1aUDj8lZrF4b4lpvejB2uB&index=14
public class MapHandler{
    private readonly IReadOnlyCollection<string> maps;
    private readonly int numberOfRounds;

    private int currentRound;
    private List<string> remainingMaps;

    public MapHandler(MapSet mapSet, int numberOfRounds){
        maps = mapSet.Maps;
        this.numberOfRounds = numberOfRounds;

        ResetMaps();
    }

    // Check if number of rounds have been reached
    public bool IsComplete => currentRound == numberOfRounds;

    // Get next map to be played
    public string NextMap{
        get{
            if(IsComplete){
                return null;
            }

            currentRound++;

            if(remainingMaps.Count == 0){
                ResetMaps();
            }

            string map = remainingMaps[UnityEngine.Random.Range(0, remainingMaps.Count)];
            remainingMaps.Remove(map);
            return map;
        }
    }

    private void ResetMaps() => remainingMaps = maps.ToList();

}
