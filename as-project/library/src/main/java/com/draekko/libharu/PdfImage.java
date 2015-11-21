/*************************************************************************

 Copyright (C) 2013-2015  Benoit Touchette

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA  02110-1301  USA

 *************************************************************************/

package com.draekko.libharu;

// ============================================================
// CLASS
// ============================================================

public class PdfImage {

    // ============================================================
    // CONSTANTS
    // ============================================================

	private final static String EVENT_NAME = "Image";

    // ============================================================
    // FIELDS
    // ============================================================

    private long HPDF_Image_Pointer;
    protected final PdfDocument parent;

    // ============================================================
    // CONSTRUCTOR
    // ============================================================

    /**
     * Image Constructor
     * @param document
     * @param fileName
     * @param usePng
     */
	public PdfImage(PdfDocument document, String fileName, boolean usePng) {
		parent = document;
        if (usePng) {
            constructPng(document, fileName);
        } else {
            constructJpeg(document, fileName);
        }
	}

    // ============================================================
    // MEMBERS / METHODS / FUNCTIONS / OVERRIDES
    // ============================================================

    /**
     * getSize
     * @return
     */
    public Point getSize() {
        Point point = new Point();
        point.x = getSizeX();
        point.y = getSizeY();
        return point;
    }

    // ============================================================
    // NATIVES
    // ============================================================

    public native int getWidth();
    public native int getHeight();
    public native int getBitsPerComponent();
    public native String getColorSpace();
    public native void setColorMask(int rmin, int rmax, int gmin, int gmax, int bmin, int bmax);
    public native void drawImage(float x, float y, float  width, float height);
	private static native void initHaru();
    private native void constructJpeg(PdfDocument document, String fileName);
    private native void constructPng(PdfDocument document, String fileName);
    private native int getSizeX();
    private native int getSizeY();

	static {
        System.loadLibrary("haru");
        initHaru();
	}

    // ============================================================
    // CLASS
    // ============================================================

    public class Point {
        int x;
        int y;
    }
}
