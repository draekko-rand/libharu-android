/*************************************************************************

 Copyright (C) 2015  Benoit Touchette

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
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.security.InvalidParameterException;
import java.util.Calendar;


// ============================================================
// CLASS
// ============================================================

public class Pdf {

    // ============================================================
    // CONSTANTS
    // ============================================================

    private static final String Serif[] = { "DroidSerif-Regular", "DroidSerif-Bold", "DroidSerif-Italic", "DroidSerif-BoldItalic" };
    private static final String Sans[] = { "Roboto-Regular", "Roboto-Bold", "Roboto-Italic", "Roboto-BoldItalic" };
    private static final String Monospace[] = { "Unispace-Regular", "Unispace-Bold", "Unispace-Italic", "Unispace-BoldItalic" };

    // ============================================================
    // FIELDS
    // ============================================================

    private Context l_context;

    // ============================================================
    // CONSTRUCTOR
    // ============================================================

    /**
     * Pdf Contructor
     * @param c_context
     */
    public Pdf (Context c_context) {
        l_context = c_context;
    }

    // ============================================================
    // MEMBERS / OVERRIDES
    // ============================================================

    /**
     * samplePdf
     * @param filename
     */
    public boolean samplePdf(String savePath, String filename) {
        String tempPath = l_context.getCacheDir().getAbsolutePath();
        boolean status = true;

        clearFile(tempPath, filename);
        clearFile(savePath, filename);

        // ===========================================================
        // Set Page sizes
        // ===========================================================

        PdfPage.PageSize defaultPageSize = PdfPage.PageSize.LETTER;
        float h_fontscaling = PdfConstants.image_dpi.DPI_HI / PdfConstants.image_dpi.DPI_MD * 0.96f;
        float p_fontscaling = PdfConstants.image_dpi.DPI_HI / PdfConstants.image_dpi.DPI_MD * 0.96f;
        float f_fontscaling = PdfConstants.image_dpi.DPI_HI / PdfConstants.image_dpi.DPI_MD * 0.96f;

        // ===========================================================
        // Set tag sizes for letter page
        // ===========================================================

        Tag defaultTags = new Tag();
        defaultTags.H1 = 32 * h_fontscaling;
        defaultTags.H2 = 28 * h_fontscaling;
        defaultTags.H3 = 26 * h_fontscaling;
        defaultTags.p  = 22 * p_fontscaling;
        defaultTags.p1 = 24 * p_fontscaling;
        defaultTags.p2 = 26 * p_fontscaling;
        defaultTags.F1 = 16 * f_fontscaling;
        defaultTags.F2 = 14 * f_fontscaling;
        defaultTags.F3 = 10 * f_fontscaling;

        // ===========================================================
        // Extract fonts
        // ===========================================================

        for (int fontitem = 0; fontitem < 4; fontitem++) {
            clearFile(tempPath, Serif[fontitem] + ".ttf");
            saveFont(tempPath, Serif[fontitem]);
        }

        for (int fontitem = 0; fontitem < 4; fontitem++) {
            clearFile(tempPath, Monospace[fontitem] + ".ttf");
            saveFont(tempPath, Monospace[fontitem]);
        }

        for (int fontitem = 0; fontitem < 4; fontitem++) {
            clearFile(tempPath, Sans[fontitem] + ".ttf");
            saveFont(tempPath, Sans[fontitem]);
        }

        // ===========================================================
        // Set up page
        // ===========================================================

        int pageCount = 1;

        FontTypes fontTypes = new FontTypes();

        PdfHelper pdfHelper = new PdfHelper(l_context);

        float page_height = pdfHelper.getHeightResolutionSize(
                PdfConstants.papertypes.LETTER,
                PdfConstants.orientation.PORTRAIT,
                PdfConstants.measurement.INCHES,
                PdfConstants.image_dpi.DPI_HI);

        float page_width = pdfHelper.getWidthResolutionSize(
                PdfConstants.papertypes.LETTER,
                PdfConstants.orientation.PORTRAIT,
                PdfConstants.measurement.INCHES,
                PdfConstants.image_dpi.DPI_HI);

        float page_dpi = PdfConstants.image_dpi.DPI_HI;

        PdfDocument document = new PdfDocument();
        document.setCompressionMode(PdfDocument.CompressionMode.COMP_ALL);

        // from https://baconipsum.com
        String bacon_ipsum = "Bacon ipsum dolor amet tenderloin kielbasa doner.";

        // ===========================================================
        // Setup Page fonts
        // ===========================================================

        fontTypes.regular = new PdfFont(document, tempPath + "/" + Serif[0] + ".ttf", true);
        fontTypes.bold = new PdfFont(document, tempPath + "/" + Serif[1] + ".ttf", true);
        fontTypes.italic = new PdfFont(document, tempPath + "/" + Serif[2] + ".ttf", true);
        fontTypes.bold_italic = new PdfFont(document, tempPath + "/" + Serif[3] + ".ttf", true);

        // ===========================================================
        // Serif Page
        // ===========================================================

        PdfPage page = document.addPage();

        BorderRect pageBorderDrawable = pageSetup(page, defaultPageSize, PdfPage.PageDirection.PORTRAIT, page_dpi);
        page.setFontAndSize(fontTypes.regular, defaultTags.H1);

        clearFile(tempPath, "a.png");
        saveImage(l_context, tempPath, "a.png", R.drawable.a);
        PdfImage image = new PdfImage(document, tempPath + "/a.png", true);

        float h, w;
        float tw = 0;
        float th = 0;

        h = image.getHeight() * 0.6f;
        w = image.getWidth() * 0.6f;
        th = 600;
        tw = (w * th) / h;

        try {
            image.drawImage(pageBorderDrawable.borderLeft, pageBorderDrawable.borderTop - th + 44, tw, th);
        } catch (Exception e) {
            e.printStackTrace();
        }

        int strokeYpos = (int) (pageBorderDrawable.borderTop - th - defaultTags.H1 + 44);

        page.setRGBStroke(0.0f, 0.0f, 0.0f);
        page.setLineCap(PdfPage.LineCap.ROUND_END);
        page.setLineJoin(PdfPage.LineJoin.ROUND_JOIN);
        page.setLineWidth(1);
        page.moveTo(pageBorderDrawable.borderLeft, strokeYpos);
        page.lineTo(pageBorderDrawable.borderRight, strokeYpos);
        page.stroke();

        int textYpos = (int) (pageBorderDrawable.borderTop - th - (defaultTags.H1 * 3) + 44);

        page.beginText();
        page.setFontAndSize(fontTypes.regular, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        textYpos -= defaultTags.H1 * 2;

        page.beginText();
        page.setFontAndSize(fontTypes.bold, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        textYpos -= defaultTags.H1 * 2;

        page.beginText();
        page.setFontAndSize(fontTypes.bold_italic, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        textYpos -= defaultTags.H1 * 2;

        page.beginText();
        page.setFontAndSize(fontTypes.italic, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        // ===========================================================
        // Setup Page fonts
        // ===========================================================

        fontTypes.regular = new PdfFont(document, tempPath + "/" + Monospace[0] + ".ttf", true);
        fontTypes.bold = new PdfFont(document, tempPath + "/" + Monospace[1] + ".ttf", true);
        fontTypes.italic = new PdfFont(document, tempPath + "/" + Monospace[2] + ".ttf", true);
        fontTypes.bold_italic = new PdfFont(document, tempPath + "/" + Monospace[3] + ".ttf", true);

        // ===========================================================
        // Monospace Page
        // ===========================================================

        page = document.addPage();

        pageBorderDrawable = pageSetup(page, defaultPageSize, PdfPage.PageDirection.PORTRAIT, page_dpi);
        page.setFontAndSize(fontTypes.regular, defaultTags.H1);

        tw = 0;
        th = 0;

        h = image.getHeight() * 0.6f;
        w = image.getWidth() * 0.6f;
        th = 600;
        tw = (w * th) / h;

        try {
            image.drawImage(pageBorderDrawable.borderLeft, pageBorderDrawable.borderTop - th + 44, tw, th);
        } catch (Exception e) {
            e.printStackTrace();
        }

        strokeYpos = (int) (pageBorderDrawable.borderTop - th - defaultTags.H1 + 44);

        page.setRGBStroke(0.0f, 0.0f, 0.0f);
        page.setLineCap(PdfPage.LineCap.ROUND_END);
        page.setLineJoin(PdfPage.LineJoin.ROUND_JOIN);
        page.setLineWidth(1);
        page.moveTo(pageBorderDrawable.borderLeft, strokeYpos);
        page.lineTo(pageBorderDrawable.borderRight, strokeYpos);
        page.stroke();

        textYpos = (int) (pageBorderDrawable.borderTop - th - (defaultTags.H1 * 3) + 44);

        page.beginText();
        page.setFontAndSize(fontTypes.regular, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        textYpos -= defaultTags.H1 * 2;

        page.beginText();
        page.setFontAndSize(fontTypes.bold, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        textYpos -= defaultTags.H1 * 2;

        page.beginText();
        page.setFontAndSize(fontTypes.bold_italic, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        textYpos -= defaultTags.H1 * 2;

        page.beginText();
        page.setFontAndSize(fontTypes.italic, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        // ===========================================================
        // Setup Page fonts
        // ===========================================================

        fontTypes.regular = new PdfFont(document, tempPath + "/" + Sans[0] + ".ttf", true);
        fontTypes.bold = new PdfFont(document, tempPath + "/" + Sans[1] + ".ttf", true);
        fontTypes.italic = new PdfFont(document, tempPath + "/" + Sans[2] + ".ttf", true);
        fontTypes.bold_italic = new PdfFont(document, tempPath + "/" + Sans[3] + ".ttf", true);

        // ===========================================================
        // Sans Page
        // ===========================================================

        page = document.addPage();

        pageBorderDrawable = pageSetup(page, defaultPageSize, PdfPage.PageDirection.PORTRAIT, page_dpi);
        page.setFontAndSize(fontTypes.regular, defaultTags.H1);

        tw = 0;
        th = 0;

        h = image.getHeight() * 0.6f;
        w = image.getWidth() * 0.6f;
        th = 600;
        tw = (w * th) / h;

        try {
            image.drawImage(pageBorderDrawable.borderLeft, pageBorderDrawable.borderTop - th + 44, tw, th);
        } catch (Exception e) {
            e.printStackTrace();
        }

        strokeYpos = (int) (pageBorderDrawable.borderTop - th - defaultTags.H1 + 44);

        page.setRGBStroke(0.0f, 0.0f, 0.0f);
        page.setLineCap(PdfPage.LineCap.ROUND_END);
        page.setLineJoin(PdfPage.LineJoin.ROUND_JOIN);
        page.setLineWidth(1);
        page.moveTo(pageBorderDrawable.borderLeft, strokeYpos);
        page.lineTo(pageBorderDrawable.borderRight, strokeYpos);
        page.stroke();

        textYpos = (int) (pageBorderDrawable.borderTop - th - (defaultTags.H1 * 3) + 44);

        page.beginText();
        page.setFontAndSize(fontTypes.regular, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        textYpos -= defaultTags.H1 * 2;

        page.beginText();
        page.setFontAndSize(fontTypes.bold, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        textYpos -= defaultTags.H1 * 2;

        page.beginText();
        page.setFontAndSize(fontTypes.bold_italic, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        textYpos -= defaultTags.H1 * 2;

        page.beginText();
        page.setFontAndSize(fontTypes.italic, defaultTags.H1);
        page.textOut(pageBorderDrawable.borderLeft, textYpos, bacon_ipsum);
        page.endText();

        // ===========================================================
        // Set file info attributes
        // ===========================================================

        document.setInfoAttr(PdfDocument.InfoType.INFO_CREATOR, "INSERT PDF CREATOR HERE");
        document.setInfoAttr(PdfDocument.InfoType.INFO_TITLE, "INSERT PDF TITLE HERE");
        document.setInfoAttr(PdfDocument.InfoType.INFO_AUTHOR, "INSERT PDF AUTHOR HERE");

        Calendar c = Calendar.getInstance();

        document.setInfoDateAttr(
                c.get(Calendar.YEAR),
                c.get(Calendar.MONTH),
                c.get(Calendar.DAY_OF_MONTH),
                c.get(Calendar.HOUR_OF_DAY),
                c.get(Calendar.MINUTE),
                c.get(Calendar.SECOND),
                PdfDocument.DateInfoType.INFO_CREATION_DATE);

        document.setInfoDateAttr(
                c.get(Calendar.YEAR),
                c.get(Calendar.MONTH),
                c.get(Calendar.DAY_OF_MONTH),
                c.get(Calendar.HOUR_OF_DAY),
                c.get(Calendar.MINUTE),
                c.get(Calendar.SECOND),
                PdfDocument.DateInfoType.INFO_MOD_DATE);

        // ===========================================================
        // setup passwords for files, enable print permission
        // ===========================================================

        document.setPassword("UseThisAsOwnerPassword", "UseThisAsUserPassword");
        document.setPermission(PdfDocument.Permissions.ENABLE_PRINT);
        document.setEncryptionMode(PdfDocument.EncryptionMode.ENCRYPT_R3_128);

        // ===========================================================
        // save to file, move to storage from cache
        // ===========================================================

        try {
            document.saveToFile(tempPath + "/" + filename);
            moveFile(tempPath, savePath, filename);
            return true;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return false;
    }


    /**
     * moveFile
     * @param originPath
     * @param filename
     * @return
     */
    public boolean clearFile(String originPath, String filename) {

        File fileOut = new File(originPath + "/" + filename);
        if (fileOut.exists()) {
            fileOut.delete();
        }

        if (!fileOut.exists()) {
            return true;
        }

        return false;
    }


    /**
     * moveFile
     * @param originPath
     * @param destinationPath
     * @param filename
     * @return
     */
    public boolean moveFile(String originPath, String destinationPath, String filename) {

        File fileIn = new File(originPath + "/" + filename);
        if (!fileIn.exists()) {
            return false;
        }

        File fileOut = new File(destinationPath + "/" + filename);
        if (fileOut.exists()) {
            fileOut.delete();
        }

        InputStream in = null;
        OutputStream out = null;
        byte[] buffer = new byte[1024];
        int read;

        try {
            in = new FileInputStream(fileIn);
            out = new FileOutputStream(fileOut);
            while ((read = in.read(buffer)) != -1) {
                out.write(buffer, 0, read);
            }
            in.close();
            out.flush();
            out.close();
            return true;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return false;
    }


    /**
     * pageSetup
     * @param page
     * @param page_size
     * @param page_orientation
     * @param width
     * @param height
     * @param dpi
     * @return
     */
    private BorderRect pageSetup(PdfPage page, PdfPage.PageSize page_size, PdfPage.PageDirection page_orientation, float width, float height, float dpi) {
        BorderRect borderDrawable = new BorderRect();

        // ===========================================================
        // Set page size to letter and orientation to portrait
        // ===========================================================

        page.setSize(page_size, page_orientation);

        // ===========================================================
        // Override default width & height sizes to match DPI
        // ===========================================================

        page.setWidth(width);
        page.setHeight(height);

        // ===========================================================
        // Set up page border sizes
        // ===========================================================

        float borderSize = dpi / 2;
        borderDrawable.borderTop = height - borderSize;
        borderDrawable.borderLeft = borderSize;
        borderDrawable.borderBottom = borderSize;
        borderDrawable.borderRight = width - borderSize;
        borderDrawable.width = width;
        borderDrawable.height = height;

        return borderDrawable;
    }


    /**
     * pageSetup
     * @param page
     * @param page_size
     * @param page_orientation
     * @param dpi
     * @return
     */
    private BorderRect pageSetup(PdfPage page, PdfPage.PageSize page_size, PdfPage.PageDirection page_orientation, float dpi) {
        float width, height;
        BorderRect borderDrawable = new BorderRect();

        // ===========================================================
        // Set page size to letter and orientation to portrait
        // ===========================================================

        page.setSize(page_size, page_orientation);

        // ===========================================================
        // Override default width & height sizes to match DPI
        // ===========================================================

        if (page_size == PdfPage.PageSize.LETTER) {
            if (page_orientation == PdfPage.PageDirection.PORTRAIT) {
                width = PdfConstants.paper.letter.portrait.inches.w * dpi;
                height = PdfConstants.paper.letter.portrait.inches.h * dpi;
            } else {
                width = PdfConstants.paper.letter.landscape.inches.w * dpi;
                height = PdfConstants.paper.letter.landscape.inches.h * dpi;
            }
        } else if (page_size == PdfPage.PageSize.LEGAL) {
            if (page_orientation == PdfPage.PageDirection.PORTRAIT) {
                width = PdfConstants.paper.legal.portrait.inches.w * dpi;
                height = PdfConstants.paper.legal.portrait.inches.h * dpi;
            } else {
                width = PdfConstants.paper.legal.landscape.inches.w * dpi;
                height = PdfConstants.paper.legal.landscape.inches.h * dpi;
            }
        } else if (page_size == PdfPage.PageSize.A3) {
            if (page_orientation == PdfPage.PageDirection.PORTRAIT) {
                width = PdfConstants.paper.A3.portrait.inches.w * dpi;
                height = PdfConstants.paper.A3.portrait.inches.h * dpi;
            } else {
                width = PdfConstants.paper.A3.landscape.inches.w * dpi;
                height = PdfConstants.paper.A3.landscape.inches.h * dpi;
            }
        } else if (page_size == PdfPage.PageSize.A4) {
            if (page_orientation == PdfPage.PageDirection.PORTRAIT) {
                width = PdfConstants.paper.A4.portrait.inches.w * dpi;
                height = PdfConstants.paper.A4.portrait.inches.h * dpi;
            } else {
                width = PdfConstants.paper.A4.landscape.inches.w * dpi;
                height = PdfConstants.paper.A4.landscape.inches.h * dpi;
            }
        } else if (page_size == PdfPage.PageSize.A5) {
            if (page_orientation == PdfPage.PageDirection.PORTRAIT) {
                width = PdfConstants.paper.A5.portrait.inches.w * dpi;
                height = PdfConstants.paper.A5.portrait.inches.h * dpi;
            } else {
                width = PdfConstants.paper.A5.landscape.inches.w * dpi;
                height = PdfConstants.paper.A5.landscape.inches.h * dpi;
            }
        } else {
            // ALL FAILLED USE DEFAULT DPI / LETTER SIZE;
            if (page_orientation == PdfPage.PageDirection.PORTRAIT) {
                width = PdfConstants.paper.letter.portrait.inches.w * 72;
                height = PdfConstants.paper.letter.portrait.inches.h * 72;
            } else {
                width = PdfConstants.paper.letter.landscape.inches.w * 72;
                height = PdfConstants.paper.letter.landscape.inches.h * 72;
            }
        }

        page.concatPage((72.0f / dpi), 0, 0, 72.0f / dpi, 0, 0);

        // ===========================================================
        // Set up page border sizes
        // ===========================================================

        float borderSize = dpi / 2;

        borderDrawable.borderTop = height - borderSize;
        borderDrawable.borderLeft = borderSize;
        borderDrawable.borderBottom = borderSize;
        borderDrawable.borderRight = width - borderSize;
        borderDrawable.width = width;
        borderDrawable.height = height;

        return borderDrawable;
    }

    /**
     * saveFont
     * @param path
     * @param fontname
     * @return
     */
    public boolean saveFont(String path, String fontname) {
        boolean status = true;

        File file = new File(path + "/" + fontname + ".ttf");
        if (file.exists()) {
            file.delete();
        }

        AssetManager assetManager = l_context.getAssets();
        InputStream in = null;
        OutputStream out = null;
        byte[] buffer = new byte[1024];
        int read;
        for (int fontitem = 0; fontitem < 4; fontitem++) {
            try {
                in = assetManager.open("fonts/" + fontname + ".ttf");
                out = new FileOutputStream(file);
                while ((read = in.read(buffer)) != -1) {
                    out.write(buffer, 0, read);
                }
                in.close();
                out.flush();
                out.close();
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }
        }

        if (!file.exists()) {
            return false;
        }

        return true;
    }

    /**
     * saveImage
     * @param c_context
     * @param c_path
     * @param c_filename
     * @param c_imageid
     * @return
     */
    public boolean saveImage(Context c_context, String c_path, String c_filename, int c_imageid) {
        if (c_context == null) throw new InvalidParameterException("c_context == null");
        File file;
        FileOutputStream fileOutputStream;

        file = new File(c_path + "/" + c_filename);

        if (file.exists()) {
            file.delete();
        }

        // Note libharu only handles jpeg/png
        try {
            //fileOutputStream = l_context.openFileOutput(c_path + "/" + c_filename, Context.MODE_PRIVATE);
            fileOutputStream = new FileOutputStream(file);
            BitmapFactory.decodeResource(l_context.getResources(), c_imageid).compress(Bitmap.CompressFormat.PNG, 100, fileOutputStream);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return false;
        }

        file = new File(c_path + "/" + c_filename);

        if (!file.exists()) {
            return false;
        }

        return true;
    }

    // ===========================================================
    // CLASS
    // ===========================================================

    private class BorderRect {
        public float borderLeft;
        public float borderRight;
        public float borderTop;
        public float borderBottom;
        public float width;
        public float height;
    }

    // ===========================================================
    // CLASS
    // ===========================================================

    private class Tag {
        public float H1;
        public float H2;
        public float H3;
        public float p;
        public float p1;
        public float p2;
        public float F1;
        public float F2;
        public float F3;
    }

    // ===========================================================
    // CLASS
    // ===========================================================

    private class FontTypes {
        public PdfFont regular;
        public PdfFont bold;
        public PdfFont italic;
        public PdfFont bold_italic;
    }
}
