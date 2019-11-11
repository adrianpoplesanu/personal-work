using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ApplicationControl : MonoBehaviour {

    void Start() {
        // add non rotation stuff
        // and never close screen light and never block the screen while running, if it's possible
    }

    void Update() {
        if (Input.GetKeyDown(KeyCode.Escape)) { 
            Application.Quit(); 
        }
    }
}
