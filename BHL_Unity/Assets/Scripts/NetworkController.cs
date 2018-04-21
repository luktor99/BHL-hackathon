using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class NetworkController : MonoBehaviour {

	const string SERVER_URL = "http://localhost:8080";
	const string REGISTRATION_URL = "/register";


	// Use this for initialization
	void Start () {
		
	}

	public Color DoConnectAndRegisterPlayer(){
		StartCoroutine (ConnectAndRegisterPlayer ());
		return Color.red;
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
	}

}
