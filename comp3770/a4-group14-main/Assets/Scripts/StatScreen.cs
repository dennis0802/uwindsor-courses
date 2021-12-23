using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;

public class StatScreen : MonoBehaviour
{
    [SerializeField]
    private TextMeshProUGUI coins, deaths, time;

    // Start is called before the first frame update
    void Start()
    {
        SetScores();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SetScores(){
        coins.text = "Coins Collected: " + PlayerPrefs.GetInt("Coins").ToString();
        time.text = "Time Taken: " + PlayerPrefs.GetFloat("Time").ToString() + " seconds";
        deaths.text = "Deaths: " + PlayerPrefs.GetInt("Deaths").ToString();
    }

    public void LoadMenu(){
        AudioManager.buttonClick.Play();
        SceneManager.LoadScene(1);
    }
}
