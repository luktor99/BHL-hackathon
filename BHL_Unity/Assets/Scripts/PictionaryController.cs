using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PictionaryController : MonoBehaviour {

	
	void OnEnable(){
		int nrOfChildren = gameObject.transform.childCount;
		for (int i = 0; i < nrOfChildren; ++i) {
			gameObject.transform.GetChild (i).transform.gameObject.SetActive (false);
		}

		int random = Random.Range (0, nrOfChildren);
		gameObject.transform.GetChild (random).transform.gameObject.SetActive (true);
	}

	void OnDisable(){
		int nrOfChildren = gameObject.transform.childCount;
		for (int i = 0; i < nrOfChildren; ++i) {
			gameObject.transform.GetChild (i).transform.gameObject.SetActive (false);
		}
	}
}

