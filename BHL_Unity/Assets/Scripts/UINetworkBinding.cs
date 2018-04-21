using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;





public class UINetworkBinding : MonoBehaviour {

	public Image playerColorBackground;

	public SelectableButton onePlayerButton;
	public SelectableButton twoPlayersButton;
	public SelectableButton threePlayersButton;
	public SelectableButton fourPlayersButton;
	public Button connectionAndRegistrationButton;
	public Button playButton;

	public SelectableButton pictionaryGameButton;
	public SelectableButton reflexGameButton;

	private SelectableButton activePlayerNumberButton;
	private SelectableButton activeGameButton;


	// Use this for initialization
	void Start () {
        onePlayerButton.onClick.AddListener(delegate { SetNumberOfPlayers(1, onePlayerButton); });
		twoPlayersButton.onClick.AddListener(delegate { SetNumberOfPlayers(2, twoPlayersButton); });
		threePlayersButton.onClick.AddListener(delegate { SetNumberOfPlayers(3, threePlayersButton); });
		fourPlayersButton.onClick.AddListener(delegate { SetNumberOfPlayers(4, fourPlayersButton); });
		connectionAndRegistrationButton.onClick.AddListener (delegate { CheckConnectionAndRegisterPlayer (); });
		pictionaryGameButton.onClick.AddListener (delegate { SetActiveGame (Game.PICTIONARY, pictionaryGameButton); });
		reflexGameButton.onClick.AddListener(delegate { SetActiveGame (Game.REFLEX, reflexGameButton); });
		playButton.onClick.AddListener (delegate { play (); });
    }
		
    void CheckConnectionAndRegisterPlayer()
    {
		Color newColor = NetworkController.Instance.DoConnectAndRegisterPlayer ();
		GameStateController.Instance.setPlayerColor (newColor);
		playerColorBackground.color = newColor;
    }

	void SetNumberOfPlayers(int numberOfPlayers, SelectableButton button)
    {
        Debug.Log("SetNumberOfPlayers: " + numberOfPlayers);
		GameStateController.Instance.setNumberOfPlayers (numberOfPlayers);
		if (activePlayerNumberButton != null) {
			activePlayerNumberButton.buttonSelected (false);
		}
		activePlayerNumberButton = button;
		activePlayerNumberButton.buttonSelected (true);
    }

	void SetActiveGame(Game game, SelectableButton button){
		Debug.Log ("Selected game: " + game);
		GameStateController.Instance.setCurrentGame (game);
		if (activeGameButton != null) {
			activeGameButton.buttonSelected (false);
		}
		activeGameButton = button;
		activeGameButton.buttonSelected (true);
	}

	void play(){
		NetworkController.Instance.DoPlayConfiguration ();
	}
    
}
