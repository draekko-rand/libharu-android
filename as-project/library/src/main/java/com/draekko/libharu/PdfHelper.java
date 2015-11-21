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


import android.content.Context;
import android.content.res.AssetManager;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

// ==========================================================
// CLASS
// ==========================================================

public class PdfHelper {

    // ==========================================================
    // CONSTANTS
    // ==========================================================

    private final static String [] mono =  { "Unispace-Regular", "Unispace-Bold", "Unispace-Italic", "Unispace-BoldItalic" };
    private final static String [] sans =  { "Roboto-Regular", "Roboto-Bold", "Roboto-Italic", "Roboto-BoldItalic" };
    private final static String [] serif =  { "DroidSerif-Regular", "DroidSerif-Bold", "DroidSerif-Italic", "DroidSerif-BoldItalic" };

    public final static int MONOSPACE = 0x1;
    public final static int SANS = 0x2;
    public final static int SERIF = 0x4;


    // ==========================================================
    // CONSTANTS
    // ==========================================================

    private Context l_context;


    // ==========================================================
    // CONSTRUCTOR
    // ==========================================================

    /**
     * PdfHelper Constructor
     * @param context
     */
    public PdfHelper(Context context){
        l_context = context;
    }


    // ==========================================================
    // MEMBERS
    // ==========================================================

    /**
     * extractFonts
     * @param c_font_type
     * @param location
     */
    public void extractFonts(int c_font_type, String location) {
        int loop = 0;

        switch (c_font_type) {
            case MONOSPACE:
                for (loop = 0; loop < mono.length; loop++) {
                    extractFontAsset(mono[loop], location);
                }
                break;

            case SANS:
                for (loop = 0; loop < sans.length; loop++) {
                    extractFontAsset(sans[loop], location);
                }
                break;

            case SERIF:
                for (loop = 0; loop < serif.length; loop++) {
                    extractFontAsset(serif[loop], location);
                }
                break;
        }
    }


    /**
     * removeFonts
     * @param location
     * @param c_font_type
     */
    public void removeFonts(String location, int c_font_type) {
        int loop = 0;

        switch (c_font_type) {
            case MONOSPACE:
                for (loop = 0; loop < mono.length; loop++) {
                    removeFontAsset(mono[loop], location);
                }
                break;

            case SANS:
                for (loop = 0; loop < sans.length; loop++) {
                    removeFontAsset(sans[loop], location);
                }
                break;

            case SERIF:
                for (loop = 0; loop < serif.length; loop++) {
                    removeFontAsset(serif[loop], location);
                }
                break;
        }
    }


    /**
     * extractFontAsset
     * @param c_filename
     * @param c_location
     */
    private void extractFontAsset(String c_filename, String c_location) {
        AssetManager assetManager = l_context.getAssets();
        byte[] buffer = new byte[1024];
        int read;
        try {
            InputStream inputStream = assetManager.open("fonts/" + c_filename);
            OutputStream outputStream = new FileOutputStream(new File(c_location + "/" + c_filename));
            while ((read = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, read);
            }
            inputStream.close();
            outputStream.flush();
            outputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * removeFontAsset
     * @param c_filename
     * @param c_location
     */
    private void removeFontAsset(String c_filename, String c_location) {
        File file = new File(c_location, c_filename);
        if (file.exists()) {
            file.delete();
        }
    }

    /**
     * getHeightResolutionSize
     * @param paper
     * @param orientation
     * @param measurement
     * @param dpi
     * @return
     */
    public float getHeightResolutionSize(int paper, int orientation, int measurement, int dpi ){
        float size = 0;

        switch(paper) {

            case PdfConstants.papertypes.A3:
                switch (orientation) {

                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.A3.portrait.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.A3.portrait.inches.h * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.A3.landscape.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.A3.landscape.inches.h * dpi);
                        }
                        break;
                }
                break;

            case PdfConstants.papertypes.A4:
                switch (orientation) {

                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.A4.portrait.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.A4.portrait.inches.h * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.A4.landscape.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.A4.landscape.inches.h * dpi);
                        }
                        break;
                }
                break;

            case PdfConstants.papertypes.LETTER:
                switch (orientation) {

                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.letter.portrait.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.letter.portrait.inches.h * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.letter.landscape.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.letter.landscape.inches.h * dpi);
                        }
                        break;
                }
                break;

            case PdfConstants.papertypes.LEGAL:
                switch (orientation) {

                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.legal.portrait.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.legal.portrait.inches.h * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.legal.landscape.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.legal.landscape.inches.h * dpi);
                        }
                        break;
                }
                break;

            case PdfConstants.papertypes.LEDGER:
                switch (orientation) {

                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.ledger.portrait.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.ledger.portrait.inches.h * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.ledger.landscape.mm.h * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.ledger.landscape.inches.h * dpi);
                        }
                        break;
                }
                break;
        }

        return size;
    }


    /**
     * getWidthResolutionSize
     * @param paper
     * @param orientation
     * @param measurement
     * @param dpi
     * @return
     */
    public float getWidthResolutionSize(int paper, int orientation, int measurement, int dpi ){
        float size = 0;

        switch(paper) {

            case PdfConstants.papertypes.A3:
                switch (orientation) {

                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.A3.portrait.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.A3.portrait.inches.w * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.A3.landscape.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.A3.landscape.inches.w * dpi);
                        }
                        break;
                }
                break;

            case PdfConstants.papertypes.A4:
                switch (orientation) {

                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.A4.portrait.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.A4.portrait.inches.w * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.A4.landscape.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.A4.landscape.inches.w * dpi);
                        }
                        break;
                }
                break;

            case PdfConstants.papertypes.LETTER:
                switch (orientation) {

                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.letter.portrait.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.letter.portrait.inches.w * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.letter.landscape.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.letter.landscape.inches.w * dpi);
                        }
                        break;
                }
                break;

            case PdfConstants.papertypes.LEGAL:
                switch (orientation) {
                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.legal.portrait.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.legal.portrait.inches.w * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.legal.landscape.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.legal.landscape.inches.w * dpi);
                        }
                        break;
                }
                break;

            case PdfConstants.papertypes.LEDGER:
                switch (orientation) {

                    case PdfConstants.orientation.PORTRAIT:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.ledger.portrait.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.ledger.portrait.inches.w * dpi);
                        }
                        break;

                    case PdfConstants.orientation.LANDSCAPE:
                        if (measurement == PdfConstants.measurement.MM) {
                            size = (float)(PdfConstants.paper.ledger.landscape.mm.w * dpi);
                        } else {
                            size = (float)(PdfConstants.paper.ledger.landscape.inches.w * dpi);
                        }
                        break;
                }
                break;
        }

        return size;
    }
}
