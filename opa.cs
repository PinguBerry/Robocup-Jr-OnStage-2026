using UnityEngine;
using UnityEngine.UI;
using System.IO.Ports;
using System.Collections.Generic;

public class opa : MonoBehaviour
{
    public GameObject cenario;
    string men = "";
    SerialPort Arduino = new SerialPort("COM3", 9600);

    float x = 0.00f;
    float y = 0.00f;

    void Men()
    {
        if (Arduino.IsOpen)
        {
            Debug.Log("Arduino is open!");
        }
    }

    void Start()
    {
        cenario.GetComponent<Transform>().position = new Vector3(x, y, 0);

        Arduino.WriteTimeout = 300;
        Arduino.ReadTimeout = 120000;
        Arduino.Open();
        Men();
    }

    void Update()
    {

        /*if (Input.GetKeyDown(KeyCode.W))
        {
            Debug.Log("W!");
            y += 2;
            cenario.GetComponent<Transform>().position = new Vector3(x, y, 0);
        }

        if (Input.GetKeyDown(KeyCode.A))
        {
            Debug.Log("A!");
            x -= 2;
            cenario.GetComponent<Transform>().position = new Vector3(x, y, 0);
        }

        if (Input.GetKeyDown(KeyCode.S))
        {
            Debug.Log("S!");
            y -= 2;
            cenario.GetComponent<Transform>().position = new Vector3(x, y, 0);
        }

        if (Input.GetKeyDown(KeyCode.D))
        {
            Debug.Log("D!");
            x += 2;
            cenario.GetComponent<Transform>().position = new Vector3(x, y, 0);
        }*/

        try
        {

            if (Arduino.BytesToRead > 0)
            {
                men = Arduino.ReadLine();
                //UnityEngine.Debug.Log("<color=#FFFF00>" + Men + "</color>"); 

                if (men == "c")
                {
                    UnityEngine.Debug.Log("<color=#FFFF00>" + men + "</color>");

                    y -= 3.61f;
                    cenario.GetComponent<Transform>().position = new Vector3(x, y, 0);
                }

                if (men == "b")
                {
                    UnityEngine.Debug.Log("<color=#FFFF00>" + men + "</color>");

                    y += 3.61f;
                    cenario.GetComponent<Transform>().position = new Vector3(x, y, 0);
                }

                if (men == "m")
                {
                    UnityEngine.Debug.Log("<color=#FFFF00>" + men + "</color>");

                    y = 0;
                    cenario.GetComponent<Transform>().position = new Vector3(x, y, 0);
                }
                
                
            }

        }
        catch
        {
            UnityEngine.Debug.Log("<color=#FFFF00> ERRO </color>");
        }
    }

}