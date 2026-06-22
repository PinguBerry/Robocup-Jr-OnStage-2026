using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using UnityEngine;

public class cacetinho: MonoBehaviour
{
    // =========================
    // GAME OBJECT REFERENCES
    // =========================

    public GameObject fantasmas;
    public GameObject fantasmashappy;
    public GameObject cenariofora1;

    public GameObject cenariofora2;
    public GameObject salabellman;
    public GameObject salabellmannormal;
    public GameObject portal;
    public GameObject chuvinhaa;

    public GameObject coralinebase;
    public GameObject coralinebasebotao;
    public GameObject branco;
    public GameObject olhos;
    public GameObject botao;

    // Audio sources for different narrative moments
    public GameObject audio1;
    public GameObject audio2;
    public GameObject audio3;
    public GameObject audio4;
    public GameObject audio5;
    public GameObject audio6;
    public GameObject audio7;

    // UI / tracking reference point in the scene
    [SerializeField] private Transform marcador;


    // =========================
    // SERIAL COMMUNICATION
    // =========================

    // Serial connections with different Arduino/Raspberry devices
    SerialPort coraline = new SerialPort("COM15", 9600); // main interaction system (portal)
    SerialPort portall = new SerialPort("COM7", 9600);    // secondary system (USB / backup)
    SerialPort gatinho = new SerialPort("COM16", 9600);   // cat interaction system

    // Incoming message buffers
    string men = "";
    string message = "";


    // =========================
    // POSITION VARIABLES
    // =========================

    float x = 0.00f;
    float y = 0.00f;
    float coordx = 0.00f;
    float coordy = 0.00f;


    // Flags for parsing serial data
    bool podex = false;
    bool podey = false;
    bool okx = false;
    bool oky = false;


    // =========================
    // STATE CONTROL FLAGS
    // =========================

    bool ok2 = false;
    bool ok3 = false;
    bool ok4 = false;
    bool ok5 = false;
    bool ok6 = false;
    bool ok7 = false;

    bool limpa = true;

    bool o = false;
    bool o1 = false;

    bool pode = false;
    bool inv = false;

    int ato = 0;

    float tempo = 0f;
    float tempo2 = 0f;
    float duracao = 3f;

    bool TargetApareceu = false;


    // =========================
    // SERIAL STATUS CHECK
    // =========================

    // Debug function to check if serial ports are open
    void Men()
    {
        if (portall.IsOpen) Debug.Log("Portal is open!");
        if (coraline.IsOpen) Debug.Log("Coraline is open!");
        if (gatinho.IsOpen) Debug.Log("Gatinho is open!");
    }


    // =========================
    // STORY CONTROL FUNCTIONS
    // =========================

    public void Aparece()
    {
        // Advances narrative stage with cooldown control
        if (tempo <= 0f)
        {
            ato++;
            tempo = duracao;
            UnityEngine.Debug.Log("coraline +" + ato);
        }
    }

    public void Aparece2()
    {
        TargetApareceu = true;
    }

    public void Desaparece()
    {
        TargetApareceu = false;
    }


    // =========================
    // SERIAL PARSING (EYE CONTROL)
    // =========================

    void OlhoNormal()
    {
        Debug.Log("entered eye tracking mode");

        try
        {
            if (coraline.BytesToRead > 0)
            {
                char men = (char)coraline.ReadChar();

                // Detect start of X or Y data stream
                if (men == 'x') okx = true;
                if (men == 'y') oky = true;

                // Parse Y value
                if (oky)
                {
                    if (men == '#')
                    {
                        Debug.Log("RECEIVED Y " + message);
                        oky = false;
                        y = float.Parse(message);

                        message = "";
                        men = ' ';
                        podey = true;
                    }
                    else
                    {
                        if (men != 'y') message += men;
                    }
                }

                // Parse X value
                else if (okx)
                {
                    if (men == '#')
                    {
                        Debug.Log("RECEIVED X " + message);
                        okx = false;
                        x = float.Parse(message);

                        message = "";
                        men = ' ';
                        podex = true;
                    }
                    else
                    {
                        if (men != 'x') message += men;
                    }
                }
            }
        }
        catch
        {
            UnityEngine.Debug.Log("<color=#FFFF00> SERIAL ERROR </color>");
        }

        // Apply Y mapping to UI position
        if (podey)
        {
            coordy = (y >= 0 && y <= 30)
                ? (2 * y) - 60
                : ((60 * y) - 1800) / 35;

            olhos.GetComponent<RectTransform>().localPosition = new Vector3(0, coordy, 0);
            podey = false;
        }

        // Apply X mapping to UI position
        else if (podex)
        {
            coordx = (x >= 50 && x <= 90)
                ? ((45 * x) - 2250) / 40
                : ((-45 * x) + 2250) / -40;

            olhos.GetComponent<RectTransform>().localPosition = new Vector3(coordx, 0, 0);
            podex = false;
        }
    }


    // =========================
    // SERIAL PARSING (ROOM SCENE CONTROL)
    // =========================

    void Sala()
    {
        try
        {
            if (coraline.BytesToRead > 0)
            {
                char men = (char)coraline.ReadChar();

                if (men == 'x') okx = true;
                if (men == 'y') oky = true;

                if (oky)
                {
                    if (men == '#')
                    {
                        oky = false;
                        y = float.Parse(message);
                        message = "";
                        podey = true;
                    }
                    else if (men != 'y')
                    {
                        message += men;
                    }
                }
                else if (okx)
                {
                    if (men == '#')
                    {
                        okx = false;
                        x = float.Parse(message);
                        message = "";
                        podex = true;
                    }
                    else if (men != 'x')
                    {
                        message += men;
                    }
                }
            }
        }
        catch
        {
            UnityEngine.Debug.Log("<color=#FFFF00> SERIAL ERROR </color>");
        }

        // Apply Y mapping for Bellman room object
        if (podey)
        {
            coordy = (y >= 0 && y <= 30)
                ? ((349 * y) - 10470) / 30
                : ((-349 * y) + 10470) / -30;

            salabellman.GetComponent<RectTransform>().localPosition = new Vector3(0, coordy, 0);
            podey = false;
        }

        // Apply X mapping for Bellman room object
        else if (podex)
        {
            coordx = (x >= 30 && x <= 90)
                ? (((615 * x) - 18450) / 60) - 615
                : ((615 * x) - 55350) / 40;

            salabellman.GetComponent<RectTransform>().localPosition = new Vector3(coordx, 0, 0);
            podex = false;
        }
    }


    // =========================
    // INITIALIZATION
    // =========================

    void Start()
    {
        // Initial UI placement
        salabellman.GetComponent<RectTransform>().localPosition = new Vector3(x, y, 0);

        // Initial scene setup (all elements hidden)
        salabellman.SetActive(false);
        salabellmannormal.SetActive(false);
        chuvinhaa.SetActive(false);
        fantasmas.SetActive(false);
        olhos.SetActive(false);
        branco.SetActive(false);
        coralinebase.SetActive(false);
        cenariofora2.SetActive(false);

        cenariofora1.SetActive(true);

        // Serial configuration
        coraline.WriteTimeout = 300;
        coraline.ReadTimeout = 120000;

        // Start background audio
        audio1.GetComponent<AudioSource>().Play();

        // Open serial connection
        coraline.Open();

        Men();
    }


    // =========================
    // MAIN UPDATE LOOP (STORY ENGINE)
    // =========================

    void Update()
    {
        tempo2 += Time.deltaTime;

        // Countdown timer for story progression
        if (tempo > 0f) tempo -= Time.deltaTime;

        // =========================
        // STORY STAGES (ATO SYSTEM)
        // =========================

        if (ato == 1)
        {
            // Rain scene activation
            cenariofora1.SetActive(true);
            chuvinhaa.SetActive(true);
            audio1.GetComponent<AudioSource>().Stop();

            if (!okc)
            {
                chuvinhaa.GetComponent<ParticleSystem>().Play();
                okc = true;
            }

            if (!ok2)
            {
                audio2.GetComponent<AudioSource>().Play();
                ok2 = true;
            }

            coraline.Write("1");
        }

        else if (ato == 2)
        {
            if (!ok3)
            {
                audio3.GetComponent<AudioSource>().Play();
                ok3 = true;
            }

            coraline.Write("2");
        }

        else if (ato == 3)
        {
            audio3.GetComponent<AudioSource>().Stop();
            coraline.Write("3");
        }

        else if (ato == 4)
        {
            chuvinhaa.SetActive(false);
            portal.SetActive(true);

            coraline.Write("4");
            portall.Write("p");
        }

        else if (ato == 5)
        {
            if (limpa)
            {
                coraline.DiscardInBuffer();
                limpa = false;
            }

            portal.SetActive(false);
            salabellman.SetActive(true);

            coraline.Write("5");
            Sala();
        }

        else if (ato == 6)
        {
            salabellman.SetActive(false);
            cenariofora2.SetActive(true);

            gatinho.Write("6");
        }

        else if (ato == 7)
        {
            salabellmannormal.SetActive(false);
            coralinebasebotao.SetActive(true);
            botao.SetActive(true);

            if (!ok4)
            {
                audio4.GetComponent<AudioSource>().Play();
                ok4 = true;
            }
        }

        else if (ato == 8)
        {
            fantasmas.SetActive(true);

            if (!ok6)
            {
                audio6.GetComponent<AudioSource>().Play();
                ok6 = true;
            }
        }

        else if (ato == 9)
        {
            if (!ok5)
            {
                audio5.GetComponent<AudioSource>().Play();
                ok5 = true;
            }
        }

        else if (ato == 10)
        {
            fantasmashappy.SetActive(true);

            if (!ok7)
            {
                audio7.GetComponent<AudioSource>().Play();
                ok7 = true;
            }
        }
    }
}
