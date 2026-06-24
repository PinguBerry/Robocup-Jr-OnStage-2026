using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.Text;

public class coraline_vision : MonoBehaviour
{
    // UDP client used to receive position data from the smartphone
    UdpClient client;

    // Communication port
    public int port = 5052;

    // Position and rotation values received through UDP
    float x = 0, z = 0, t = 0;

    // ==================== START ====================
    void Start()
    {
        // Initialize UDP listener
        Debug.Log("Starting UDP listener");

        client = new UdpClient(port);

        Debug.Log("Listening on port 5052");

        // Start asynchronous reception
        client.BeginReceive(ReceiveData, null);
    }

    // ==================== VOID RECEIVE DATA ====================
    void ReceiveData(System.IAsyncResult result)
    {
        Debug.Log("Data received");

        // Create endpoint to receive incoming packets
        IPEndPoint ip = new IPEndPoint(IPAddress.Any, port);

        // Read received bytes
        byte[] data = client.EndReceive(result, ref ip);

        string buffer = "";

        // Convert bytes to UTF-8 string
        string text = Encoding.UTF8.GetString(data);

        buffer += text;

        Debug.Log(text);

        // Process all complete messages contained in the buffer
        while (true)
        {
            int start = buffer.IndexOf('@');
            int end = buffer.IndexOf('#');

            // Messages follow the format:
            // @xVALUEzVALUEtVALUE#
            if (start != -1 && end != -1 && end > start)
            {
                string mensagem = buffer.Substring(start + 1, end - start - 1);

                ProcessarMensagem(mensagem);

                // Remove processed message from buffer
                buffer = buffer.Substring(end + 1);
            }
            else
            {
                break;
            }
        }

        // Continue listening for new packets
        client.BeginReceive(ReceiveData, null);
    }

//==================== DECODE THE MESSAGE ====================
    void ProcessarMensagem(string msg)
    {
        int i = 0;

        // Parse each variable contained in the message
        while (i < msg.Length)
        {
            char tipo = msg[i];
            i++;

            string numero = "";

            // Extract numeric value associated with the variable
            while (i < msg.Length && !char.IsLetter(msg[i]))
            {
                numero += msg[i];
                i++;
            }

            // Standardize decimal separator
            numero = numero.Replace(",", ".");

            float valor = float.Parse(
                numero,
                System.Globalization.CultureInfo.InvariantCulture
            );

            // Store received values
            switch (tipo)
            {
                case 'x':
                    x = valor;
                    break;

                case 'z':
                    z = valor;
                    break;

                case 't':
                    t = valor;
                    break;
            }
        }

        // Display received coordinates for debugging
        Debug.Log($"X:{x} Z:{z} T:{t}");
    }
//==================== VOID UPDATE ====================
    void Update()
    {
        // Update object position using received coordinates
        transform.position = new Vector3(x, 9.2f, z);

        // Update object rotation around Y-axis
        transform.rotation = Quaternion.Euler(0, t, 0);
    }
}
