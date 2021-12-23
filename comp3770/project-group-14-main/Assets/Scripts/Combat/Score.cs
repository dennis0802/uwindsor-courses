using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;

// Score tracking class
public class Score : NetworkBehaviour
{
    [SyncVar]
    public int blueScore = 0, redScore = 0;

}
