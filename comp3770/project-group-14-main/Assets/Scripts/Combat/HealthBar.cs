using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Mirror;

// Based off of: https://www.youtube.com/watch?v=K5TUj1VnF5M
public class HealthBar : NetworkBehaviour
{
    [Header("References")]
    [SerializeField] private Health health = null;
    [SerializeField] private Slider slider = null;

    private void OnEnable(){
        health.EventHealthChanged += HandleHealthChanged;
    }
    private void OnDisable(){
        health.EventHealthChanged -= HandleHealthChanged;
    }

    [ClientRpc]
    private void HandleHealthChanged(int currentHealth,int maxHealth){
        slider.value = currentHealth;
    }
}
