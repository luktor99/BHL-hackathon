using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;
using System.Timers;

public class NetworkController : MonoBehaviour {

	const bool production = true;

	const string SERVER_URL = "http://192.168.4.1";
	const string MOCK_URL = "https://c74d8ef8-bac3-40a0-a41e-1c6e1bf1a51a.mock.pstmn.io";
	const string REGISTRATION_URL = "/register";
	const string GAME_URL = "/game?params=";
	const string REFLEX_INFO_URL = "/react";
	const string PICTIONARY_INFO_URL = "/pictionary";
	const string RESET_URL = "/reset";



	void Start(){
		StartCoroutine (ReflexInfoPoll ());
		StartCoroutine (PictionaryInfoPoll ());
	}
		
		

	void OnPlayerReadyMessage(NetworkMessage msg){
		Debug.Log (msg.ToString ());
	}

	public void DoConnectAndRegisterPlayer(){
		StartCoroutine (ConnectAndRegisterPlayer ());
	}

	public void DoPlayConfiguration(){
		StartCoroutine (PlayConfiguration ());
	}

	public void DoReset(){
		StartCoroutine (ResetGame ());
	}

	IEnumerator ResetGame(){
		UnityWebRequest www;
		if (production) {
			www = UnityWebRequest.Get (SERVER_URL + RESET_URL);
		} else {
			www = UnityWebRequest.Get (MOCK_URL + RESET_URL);
		}
		yield return www.SendWebRequest ();

		if(www.isNetworkError || www.isHttpError) {
			Debug.Log(www.error);
			UINetworkBinding.Instance.toastServerError (www.responseCode);
		}
		else {
			Debug.Log("Request response code: " + www.responseCode);
			Debug.Log("Request succesfull: " + www.downloadHandler.text);
			UINetworkBinding.Instance.resetSuccess ();
		}
	}

	IEnumerator ReflexInfoPoll(){
		while (true) {
			if (GameStateController.Instance.getCurrentGame () == Game.REFLEX) {
				Debug.Log ("ReflexInfo called");
				UnityWebRequest wwwPoll;
				string reqDest = "";
				if (production) {
					reqDest = SERVER_URL + REFLEX_INFO_URL;
					wwwPoll = UnityWebRequest.Get (reqDest);
				} else {
					reqDest = MOCK_URL + REFLEX_INFO_URL;
					wwwPoll = UnityWebRequest.Get (reqDest);
				}
				Debug.Log ("Request: " + reqDest);

				yield return wwwPoll.SendWebRequest ();

				if (wwwPoll.isNetworkError || wwwPoll.isHttpError) {
					Debug.Log (wwwPoll.error);
					UINetworkBinding.Instance.toastServerError (wwwPoll.responseCode);

				} else {
					Debug.Log ("Request response code: " + wwwPoll.responseCode);
					Debug.Log ("Request succesfull: " + wwwPoll.downloadHandler.text);
					UINetworkBinding.Instance.translateReflexInfo (wwwPoll.downloadHandler.text);
				}	
			}
			yield return new WaitForSeconds (0.2f);
			//Debug.Log ("After timer");
		}

	}

	IEnumerator PictionaryInfoPoll(){
		while (true) {
			if (GameStateController.Instance.getCurrentGame () == Game.PICTIONARY) {
				Debug.Log ("PictionaryInfo called");
				UnityWebRequest wwwPoll;
				string reqDest = "";
				if (production) {
					reqDest = SERVER_URL + PICTIONARY_INFO_URL;
					wwwPoll = UnityWebRequest.Get (reqDest);
				} else {
					reqDest = MOCK_URL + PICTIONARY_INFO_URL;
					wwwPoll = UnityWebRequest.Get (reqDest);
				}
				Debug.Log ("Request: " + reqDest);

				yield return wwwPoll.SendWebRequest ();

				if (wwwPoll.isNetworkError || wwwPoll.isHttpError) {
					Debug.Log (wwwPoll.error);
					if (Application.platform == RuntimePlatform.Android) {
						UINetworkBinding.Instance.toastServerError (wwwPoll.responseCode);
					}
				} else {
					Debug.Log ("Request response code: " + wwwPoll.responseCode);
					Debug.Log ("Request succesfull: " + wwwPoll.downloadHandler.text);
					UINetworkBinding.Instance.translatePictionaryInfo (wwwPoll.downloadHandler.text);
				}
			}
			yield return new WaitForSeconds (0.2f);
		}

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
