using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SelectableButton : Button {

	public Sprite unSelectedSprite;
	public Sprite selectedSprite;

	public void buttonSelected(bool state){
		if(state){
			this.image.sprite = selectedSprite;
		}else{
			this.image.sprite = unSelectedSprite;
		}
	}
}
