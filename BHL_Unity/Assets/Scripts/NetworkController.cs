using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class NetworkController : MonoBehaviour {

	const bool production = true;

	const string SERVER_URL = "http://192.168.4.1";
	const string MOCK_URL = "https://c74d8ef8-bac3-40a0-a41e-1c6e1bf1a51a.mock.pstmn.io";
	const string REGISTRATION_URL = "/register";
	const string GAME_URL = "/game?params=";



	public void DoConnectAndRegisterPlayer(){
		StartCoroutine (ConnectAndRegisterPlayer ());
	}

	public void DoPlayConfiguration(){
		StartCoroutine (PlayConfiguration ());
	}

	IEnumerator PlayConfiguration(){
		Debug.Log ("Sending configuration: Game: " + GameStateController.Instance.getCurrentGame ()
			+ " nr of players: " + GameStateController.Instance.getNumberOfPlayers ());
		UnityWebRequest www;
		string reqDest = "";
		if (production) {
			www = UnityWebRequest.Get (SERVER_URL + GAME_URL);
			if (GameStateController.Instance.getCurrentGame () == Game.REFLEX) {
				reqDest = SERVER_URL + GAME_URL + GameStateController.Instance.getNumberOfPlayers () + "React";
				www = UnityWebRequest.Get (reqDest);
			} else if (GameStateController.Instance.getCurrentGame () == Game.PICTIONARY) {
				reqDest = SERVER_URL + GAME_URL + GameStateController.Instance.getNumberOfPlayers () + "Kalam";
				www = UnityWebRequest.Get (reqDest);
			}
		} else {
			www = UnityWebRequest.Get (MOCK_URL + GAME_URL);
			if (GameStateController.Instance.getCurrentGame () == Game.REFLEX) {				
				reqDest = MOCK_URL + GAME_URL + GameStateController.Instance.getNumberOfPlayers () + "React";
				www = UnityWebRequest.Get (reqDest);
			} else if (GameStateController.Instance.getCurrentGame () == Game.PICTIONARY) {
				reqDest = MOCK_URL + GAME_URL + GameStateController.Instance.getNumberOfPlayers () + "Kalam";
				www = UnityWebRequest.Get (reqDest);
			}
		}
		Debug.Log ("Request: " + reqDest);

		yield return www.SendWebRequest ();

		if(www.isNetworkError || www.isHttpError) {
			Debug.Log(www.error);
			UINetworkBinding.Instance.toastServerError (www.responseCode);
		}
		else {
			Debug.Log("Request response code: " + www.responseCode);
			Debug.Log("Request succesfull: " + www.downloadHandler.text);
			UINetworkBinding.Instance.playSuccess ();
		}
	}
	
	IEnumerator ConnectAndRegisterPlayer(){
		UnityWebRequest www;
		if (production) {
			www = UnityWebRequest.Get (SERVER_URL + REGISTRATION_URL);
		} else {
			www = UnityWebRequest.Get (MOCK_URL + REGISTRATION_URL);
		}
		yield return www.SendWebRequest ();

		if(www.isNetworkError || www.isHttpError) {
			Debug.Log(www.error);
			UINetworkBinding.Instance.toastServerError (www.responseCode);
		}
		else {
			Debug.Log("Request response code: " + www.responseCode);
			Debug.Log("Request succesfull: " + www.downloadHandler.text);
			UINetworkBinding.Instance.ConnectionSuccess (Color.red);
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
