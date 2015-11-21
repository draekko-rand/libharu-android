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

public class PdfConstants {

    // ================================================================
    // MEASUREMENTS TOKEN
    // ================================================================

    public class orientation {
        public static final int PORTRAIT  = 0x0001;
        public static final int LANDSCAPE = 0x0002;
    }

    // ================================================================
    // MEASUREMENTS TOKEN
    // ================================================================

    public class measurement {
        public static final int PIXELS  = 0x0001;
        public static final int INCHES  = 0x0002;
        public static final int MM      = 0x0004;
    }


    // ================================================================
    // PAPER TYPES
    // ================================================================

    public class papertypes {
        public static final int LETTER  = 0x0001;
        public static final int LEGAL   = 0x0002;
        public static final int A3      = 0x0004;
        public static final int A4      = 0x0008;
        public static final int A5      = 0x0010;
        public static final int LEDGER  = 0x0020;
    }


    // ================================================================
    // PDF DPI SETTINGS
    // ================================================================

    public class image_dpi {
        public static final int DPI_LO = 75;
        public static final int DPI_MD = 150;
        public static final int DPI_HI = 300;
        public static final int DPI_XHI = 600;
    }

    // ================================================================
    // PAPER SIZES
    // ================================================================

    public class paper {

        // =====================
        // LETTER SHEETS
        // =====================

        public class letter {

            // LETTER PORTRAIT
            public class portrait {

                // MILLIMETERS
                public class mm {
                    public static final float w = 215;
                    public static final float h = 280;
                }

                // INCHES
                public class inches {
                    public static final float w = 8.5f;
                    public static final float h = 11f;
                }
            }

            // LETTER LANDSCAPE
            public class landscape {

                // MILLIMETERS
                public class mm {
                    public static final float w = 280;
                    public static final float h = 215;
                }

                // INCHES
                public class inches {
                    public static final float w = 11f;
                    public static final float h = 8.5f;
                }
            }
        }

        // =====================
        // LEGAL SHEETS
        // =====================

        public class legal {

            // LEGAL PORTRAIT
            public class portrait {

                // MILLIMETERS
                public class mm {
                    public static final float w = 215;
                    public static final float h = 355;
                }

                // INCHES
                public class inches {
                    public static final float w = 8.5f;
                    public static final float h = 14f;
                }
            }

            // LEGAL LANDSCAPE
            public class landscape {

                // MILLIMETERS
                public class mm {
                    public static final float w = 355;
                    public static final float h = 215;
                }

                // INCHES
                public class inches {
                    public static final float w = 14f;
                    public static final float h = 8.5f;
                }
            }
        }

        // =====================
        // LEDGER SHEETS
        // =====================

        public class ledger {

            // LEDGER PORTAIT
            public class portrait {

                // MILLIMETERS
                public class mm {
                    public static final float w = 279;
                    public static final float h = 432;
                }

                // INCHES
                public class inches {
                    public static final float w = 11f;
                    public static final float h = 17f;
                }
            }

            // LEDGER LANDSCAPE
            public class landscape {

                // MILLIMETERS
                public class mm {
                    public static final float w = 432;
                    public static final float h = 279;
                }

                // INCHES
                public class inches {
                    public static final float w = 17f;
                    public static final float h = 11f;
                }
            }
        }

        // =====================
        // A3 SHEETS
        // =====================

        public class A3 {

            // A3 PORTAIT
            public class portrait {

                // MILLIMETERS
                public class mm {
                    public static final float w = 297;
                    public static final float h = 420;
                }

                // INCHES
                public class inches {
                    public static final float w = 11.7f;
                    public static final float h = 16.5f;
                }
            }

            // A3 LANDSCAPE
            public class landscape {

                // MILLIMETERS
                public class mm {
                    public static final float w = 420;
                    public static final float h = 297;
                }

                // INCHES
                public class inches {
                    public static final float w = 16.5f;
                    public static final float h = 11.7f;
                }
            }
        }

        // =====================
        // A4 SHEETS
        // =====================

        public class A4 {

            // A4 PORTAIT
            public class portrait {

                // MILLIMETERS
                public class mm {
                    public static final float w = 210;
                    public static final float h = 297;
                }

                // INCHES
                public class inches {
                    public static final float w = 8.3f;
                    public static final float h = 11.7f;
                }
            }

            // A4 LANDSCAPE
            public class landscape {

                // MILLIMETERS
                public class mm {
                    public static final float w = 297;
                    public static final float h = 210;
                }

                // INCHES
                public class inches {
                    public static final float w = 11.7f;
                    public static final float h = 8.3f;
                }
            }
        }

        // =====================
        // A5 SHEETS
        // =====================

        public class A5 {

            // A5 PORTAIT
            public class portrait {

                // MILLIMETERS
                public class mm {
                    public static final float w = 148;
                    public static final float h = 210;
                }

                // INCHES
                public class inches {
                    public static final float w = 5.83f;
                    public static final float h = 8.27f;
                }
            }

            // A5 LANDSCAPE
            public class landscape {

                // MILLIMETERS
                public class mm {
                    public static final float w = 210;
                    public static final float h = 148;
                }

                // INCHES
                public class inches {
                    public static final float w = 8.27f;
                    public static final float h = 5.83f;
                }
            }
        }
    }
}
