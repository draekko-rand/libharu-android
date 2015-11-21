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

import java.io.IOException;
import java.util.LinkedList;
import java.util.ListIterator;

// ============================================================
// CLASS
// ============================================================

public class PdfDocument {

    // ============================================================
    // CONSTANTS
    // ============================================================

	private static final String EVENT_NAME = "Document";

    public enum CompressionMode {
        COMP_NONE, COMP_TEXT, COMP_IMAGE, COMP_METADATA, COMP_ALL
    }

    public class Permissions {
        public static final int ENABLE_READ     = 0x00;
        public static final int ENABLE_PRINT    = 0x04;
        public static final int ENABLE_EDIT_ALL = 0x08;
        public static final int ENABLE_COPY     = 0x10;
        public static final int ENABLE_EDIT     = 0x20;
    }

    public enum EncryptionMode {
        ENCRYPT_R2,  ENCRYPT_R3_40,  ENCRYPT_R3_128;
    }

    public class DateInfoType {
        public static final int INFO_CREATION_DATE = 0x1;
        public static final int INFO_MOD_DATE      = 0x2;
    }

    public class InfoType {
        public static final int INFO_AUTHOR   = 0x01;
        public static final int INFO_CREATOR  = 0x02;
        public static final int INFO_TITLE    = 0x04;
        public static final int INFO_SUBJECT  = 0x08;
        public static final int INFO_KEYWORDS = 0x10;
    }

    // ============================================================
    // FIELDS
    // ============================================================

    private long HPDF_Doc_Pointer;
	protected LinkedList<PdfPage> pages = new LinkedList<PdfPage>();

    // ============================================================
    // CONSTRUCTOR
    // ============================================================

    /**
     * PdfDocument Constructor
     */
	public PdfDocument() {
		construct();
	}

    // ============================================================
    // MEMBERS / METHODS / FUNCTIONS / OVERRIDES
    // ============================================================

    /**
     * addPage
     * @return
     */
	public PdfPage addPage() {
		return new PdfPage(this);
	}

	// It is your responsibility to call Document.destructAll() when you are finished.

    /**
     * destructAll
     * It's your responsibility to call Document.destructAll() when done.
     */
	public void destructAll() {
		ListIterator<PdfPage> iter = pages.listIterator();
		while (iter.hasNext())
			iter.next().destruct();
		destruct();
	}

    /**
     * getFont
     * @param font
     * @param encodingName
     * @return
     */
	public PdfFont getFont(PdfFont.HaruFont font, String encodingName) {
		return new PdfFont(this, font, encodingName);
	}

    /**
     * getFont
     * @param font
     * @return
     */
	public PdfFont getFont(PdfFont.HaruFont font) {
		return new PdfFont(this, font);
	}

    /**
     * getFont
     * @param fontPathName
     * @param embbeded
     * @return
     */
    public PdfFont getFont(String fontPathName, boolean embbeded) {
        return new PdfFont(this, fontPathName, embbeded);
    }

    // ============================================================
    // NATIVES
    // ============================================================

    public native void saveToFile(String filename) throws IOException;
    public native void setCompressionMode(CompressionMode compressionMode);
    public native void setPermission(int permissions);
    public native void setEncryptionMode(EncryptionMode encryptionMode);
    public native void setPassword(String ownerPassword, String userPassword);
    public native void setInfoDateAttr(int year, int month, int day, int hour, int minutes, int seconds, int dateInfoType);
    public native void setInfoAttr(int type, String valu10e);
	private static native void initHaru();
	private native void construct();
	private native void destruct();

	static {
        System.loadLibrary("haru");
        initHaru();
    }
}
