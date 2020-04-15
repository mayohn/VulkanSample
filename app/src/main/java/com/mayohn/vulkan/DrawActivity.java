package com.mayohn.vulkan;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.widget.LinearLayout;

import androidx.annotation.Nullable;


public class DrawActivity extends Activity {
    private LinearLayout layout;
    private GLSurfaceView glSurfaceView;
    private GLSurfaceView.Renderer renderer;
    private boolean rendererSet;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_draw);
        layout = findViewById(R.id.layout);
        glSurfaceView = new GLSurfaceView(this);
        glSurfaceView.setEGLContextClientVersion(3);
        int i = getIntent().getIntExtra("Type", 0);
        switch (i) {
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
        }
        glSurfaceView.setRenderer(renderer);
        rendererSet = true;
        layout.removeAllViews();
        layout.addView(glSurfaceView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (rendererSet) {
            glSurfaceView.onResume();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (rendererSet) {
            glSurfaceView.onPause();
        }
    }
}
