using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputHandler : MonoBehaviour {
    //public SpriteRenderer target; 
    // mai bine folosesc o referinta catre obiectul care randeaza imaginea si pun un script pe el si apelez o metoda din el care incarca imaginea de pe disk
    //public GameObject canvas; // TODO: change this to a sprite renderer and change canvas.GetComponent<ImageLoader>() to SpriteRenderer.sprite = ...
    // this is needed bevcause i'm removing the canvas from the scene
    public GameObject target;

    void Start() {
        
    }

    // Update is called once per frame
    void Update() {
        if ((Input.touchCount > 0) && (Input.GetTouch(0).phase == TouchPhase.Began)) {
            Vector3 mousePos = Camera.main.ScreenToWorldPoint(Input.GetTouch(0).position);
            Vector2 mousePos2D = new Vector2(mousePos.x, mousePos.y);
            RaycastHit2D raycastHit = Physics2D.Raycast(mousePos2D, Vector2.zero);
            if (raycastHit) {
                Debug.Log("Something Hit");
                if (raycastHit.collider.CompareTag("ChooseImageButton")) {
                    NativeGallery.Permission permission = NativeGallery.GetImageFromGallery( ( path ) => {
                        //path = "/storage/emmc/DCIM/Camera/IMG_20191020_140006.jpg";
                        //path = "D:\\Documents\\unity\\ramona1\\adri.jpg";
                        //path = "/storage/emulated/0/DCIM/Camera/IMG_20191008_002926.jpg";
                        Debug.Log( "Image path: " + path );
                        if( path != null ) {
                            //canvas.GetComponent<ImageLoader>().url = path;
                            //canvas.GetComponent<ImageLoader>().RefreshImage();
                            target.GetComponent<MainImageRenderer>().RefreshImage(path);
                        } else {
                            Debug.Log("what happened???");
                        }
                    }, "Select a PNG image", "image/png" );
                }
                if (raycastHit.collider.CompareTag("HealButton")) {
                    Debug.Log("HealButton clicked");
                }
            } else {
                Debug.Log("Something DIDN'T Hit");
            }
        }        
    }
}
