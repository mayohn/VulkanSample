package com.mayohn.vulkan.jni;


import android.view.Surface;

public class JniRenderer {
    static {
        System.loadLibrary("renderer");
    }

    public native void setGLSLPath(String path, String tag);

    public native void onSurfaceCreated(Surface view);

    public native void onSurfaceChanged(int width, int height);

    public native void surfaceDestroyed();

    public native void onDrawFrame();
}
