using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BatteryStatusUIController : MonoBehaviour {

	public Sprite batteryFull;
	public Sprite batteryNearlyFull;
	public Sprite batteryHalf;
	public Sprite batteryNearlyEmpty;
	public Sprite batteryEmpty;

	public Image batteryImage;

	public void setBatteryLevel(int level){
		 if (level == 1) {
			batteryImage.sprite = batteryNearlyEmpty;
		} else if (level == 2) {
			batteryImage.sprite = batteryHalf;
		} else if (level == 3) {
			batteryImage.sprite = batteryNearlyFull;
		} else if (level == 4) {
			batteryImage.sprite = batteryFull;
		}
	}

}
