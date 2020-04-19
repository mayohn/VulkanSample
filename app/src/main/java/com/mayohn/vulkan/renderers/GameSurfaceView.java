package com.mayohn.vulkan.renderers;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GameSurfaceView extends SurfaceView implements SurfaceHolder.Callback, Runnable {

    boolean mbLoop = false;
    SurfaceHolder mSurfaceHolder = null;

    int count = 0;
    float x = 50, y = 50;
    int screenWidth = 480, screenHeight = 800;

    public GameSurfaceView(Context context) {
        super(context);

        mbLoop = true;

        mSurfaceHolder = this.getHolder();
        mSurfaceHolder.addCallback(this);
        this.setFocusable(true);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        new Thread(this).start();   // start paint thread
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        screenWidth = width;        // reset width when screen orientation is changed
        screenHeight = height;      // reset height when screen orientation is changed
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        mbLoop = false;
    }

    @Override
    public void run() {
        while (mbLoop) {
            synchronized (mSurfaceHolder) {
                draw();
            }

            try {
                Thread.sleep(200);
            } catch (Exception e) {
            }
        }
    }

    public void draw() {
        Canvas canvas = mSurfaceHolder.lockCanvas();
        if (mSurfaceHolder == null || canvas == null) {
            return;
        }

        if (count < 100) {
            count++;
        } else {
            count = 0;
        }

        Paint mPaint = new Paint();
        mPaint.setAntiAlias(true);
        mPaint.setColor(Color.CYAN);
        canvas.drawRect(0, 0, screenWidth, screenHeight, mPaint);   // repaint background color
        switch (count % 4) {
            case 0:
                mPaint.setColor(Color.BLUE);
                break;
            case 1:
                mPaint.setColor(Color.GREEN);
                break;
            case 2:
                mPaint.setColor(Color.RED);
                break;
            case 3:
                mPaint.setColor(Color.YELLOW);
                break;
            default:
                mPaint.setColor(Color.WHITE);
                break;
        }
        canvas.drawCircle(x, y, 50, mPaint);
        mSurfaceHolder.unlockCanvasAndPost(canvas);
    }
}