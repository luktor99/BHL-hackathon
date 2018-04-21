using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class NetworkController : MonoBehaviour {


	const string SERVER_URL = "http://192.168.4.1:8080";
	const string REGISTRATION_URL = "/register";
	const string GAME_URL = "/game";



	public Color DoConnectAndRegisterPlayer(){
		StartCoroutine (ConnectAndRegisterPlayer ());
		return Color.red;
	}

	public void DoPlayConfiguration(){
		StartCoroutine (PlayConfiguration ());
	}

	IEnumerator PlayConfiguration(){
		Debug.Log ("Sending configuration: Game: " + GameStateController.Instance.getCurrentGame ()
			+ " nr of players: " + GameStateController.Instance.getNumberOfPlayers ());

		UnityWebRequest www = UnityWebRequest.Get (SERVER_URL + GAME_URL);
		yield return www.SendWebRequest ();

		if(www.isNetworkError || www.isHttpError) {
			Debug.Log(www.error);
		}
		else {
			Debug.Log("Request response code: " + www.responseCode);
			Debug.Log("Request succesfull: " + www.downloadHandler.text);
		}
	}
	
	IEnumerator ConnectAndRegisterPlayer(){
		UnityWebRequest www = UnityWebRequest.Get (SERVER_URL + REGISTRATION_URL);
		yield return www.SendWebRequest ();

		if(www.isNetworkError || www.isHttpError) {
			Debug.Log(www.error);
		}
		else {
			Debug.Log("Request response code: " + www.responseCode);
			Debug.Log("Request succesfull: " + www.downloadHandler.text);
		}

		//TODO Get battery level from response
	}

	private static NetworkController _instance;

	public static NetworkController Instance { get { return _instance; } }

	private void Awake(){
		if (_instance != null && _instance != this) {
			Destroy (this.gameObject);
		} else {
			_instance = this;
		}
	}


}
