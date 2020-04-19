package com.mayohn.vulkan.renderers;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;


import com.mayohn.vulkan.jni.JniRenderer;

import java.io.File;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class BaseRenderer extends SurfaceView implements SurfaceHolder.Callback, Runnable {
    private static String TAG = "BaseRenderer";
    protected String name = "ParentRenderer";
    private static final String SEPARATOR = File.separator;//路径分隔符
    protected SurfaceHolder surfaceHolder;
    protected JniRenderer jniRenderer;
    protected String mGLSLPath;

    BaseRenderer(Context context, String name) {
        super(context);
        this.name = name;
        mGLSLPath = context.getApplicationContext().getExternalFilesDir(null).getAbsolutePath() + SEPARATOR + "glsl" + SEPARATOR;
        jniRenderer = new JniRenderer();
        jniRenderer.setGLSLPath(mGLSLPath, name);
        surfaceHolder = this.getHolder();
        surfaceHolder.addCallback(this);
        this.setFocusable(true);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        Log.i(TAG, "surfaceCreated: ");
        new Thread(this).start();
        jniRenderer.onSurfaceCreated(holder.getSurface());
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.i(TAG, "surfaceChanged: ");
        jniRenderer.onSurfaceChanged(width, height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        Log.i(TAG, "surfaceDestroyed: ");
        jniRenderer.surfaceDestroyed();
    }

    @Override
    public void run() {
        Log.i(TAG, "run: ");
        jniRenderer.onDrawFrame();
    }
}
