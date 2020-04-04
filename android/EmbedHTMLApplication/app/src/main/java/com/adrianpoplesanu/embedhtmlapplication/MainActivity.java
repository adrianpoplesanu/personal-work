package com.adrianpoplesanu.embedhtmlapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.webkit.WebView;

public class MainActivity extends AppCompatActivity {

    private WebView webViewWebPage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        webViewWebPage = findViewById(R.id.webViewWebPage);
        loadHTMLPage();
    }

    private void loadHTMLPage() {
        webViewWebPage.getSettings().setJavaScriptEnabled(true);
        webViewWebPage.loadUrl("file:///android_asset/index.html");
    }
}
