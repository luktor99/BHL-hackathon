using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;





public class UINetworkBinding : MonoBehaviour {


	public NetworkController networkController;
	public Image playerColorBackground;

	public Button onePlayerButton;
	public Button twoPlayersButton;
	public Button threePlayersButton;
	public Button fourPlayersButton;
	public Button connectionAndRegistrationButton;


	// Use this for initialization
	void Start () {
        onePlayerButton.onClick.AddListener(delegate { SetNumberOfPlayers(1); });
		twoPlayersButton.onClick.AddListener(delegate { SetNumberOfPlayers(2); });
		threePlayersButton.onClick.AddListener(delegate { SetNumberOfPlayers(3); });
		fourPlayersButton.onClick.AddListener(delegate { SetNumberOfPlayers(4); });
		connectionAndRegistrationButton.onClick.AddListener (delegate { CheckConnectionAndRegisterPlayer (); });
    }
		
    void CheckConnectionAndRegisterPlayer()
    {
		Color newColor = networkController.DoConnectAndRegisterPlayer ();
		GameStateController.Instance.setPlayerColor (newColor);
		playerColorBackground.color = newColor;
    }

    void SetNumberOfPlayers(int numberOfPlayers)
    {
        Debug.Log("SetNumberOfPlayers: " + numberOfPlayers);
    }
    
}
