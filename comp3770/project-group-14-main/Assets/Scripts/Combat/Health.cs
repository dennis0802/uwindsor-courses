using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;
//test shooting
//using Cinemachine;
// Based off of: https://www.youtube.com/watch?v=K5TUj1VnF5M
public class Health : NetworkBehaviour
{
    [Header("Settings")]
    [SerializeField] private int maxHealth = 100;
    [SyncVar]
    public int currentHealth;
    
    public delegate void HealthChangedDelegate(int currentHealth,int maxHealth);

    public event HealthChangedDelegate EventHealthChanged;

    public override void OnStartAuthority(){
        enabled = true;
    }

    [Server]
    public void SetHealth(int value){
        currentHealth = value;
        EventHealthChanged?.Invoke(currentHealth,maxHealth);
    }

    public override void OnStartServer() => SetHealth(maxHealth);
}
