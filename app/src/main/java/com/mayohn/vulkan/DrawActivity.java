package com.mayohn.vulkan;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceView;
import android.widget.LinearLayout;

import androidx.annotation.Nullable;

import com.mayohn.vulkan.renderers.BaseRenderer;
import com.mayohn.vulkan.renderers.GameSurfaceView;
import com.mayohn.vulkan.renderers.Program01Renderer;


public class DrawActivity extends Activity {
    private SurfaceView surfaceView;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        int i = getIntent().getIntExtra("Type", 0);
        switch (i) {
            case 0:
                surfaceView = new GameSurfaceView(this);
                break;
            case 1:
                surfaceView = new Program01Renderer(this);
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
        }
        setContentView(surfaceView);
    }
}
