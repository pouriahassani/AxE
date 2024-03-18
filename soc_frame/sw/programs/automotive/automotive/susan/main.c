/* {{{ Copyright etc. */

/**********************************************************************\

  SUSAN Version 2l by Stephen Smith
  Oxford Centre for Functional Magnetic Resonance Imaging of the Brain,
  Department of Clinical Neurology, Oxford University, Oxford, UK
  (Previously in Computer Vision and Image Processing Group - now
  Computer Vision and Electro Optics Group - DERA Chertsey, UK)
  Email:    steve@fmrib.ox.ac.uk
  WWW:      http://www.fmrib.ox.ac.uk/~steve

  (C) Crown Copyright (1995-1999), Defence Evaluation and Research Agency,
  Farnborough, Hampshire, GU14 6TD, UK
  DERA WWW site:
  http://www.dera.gov.uk/
  DERA Computer Vision and Electro Optics Group WWW site:
  http://www.dera.gov.uk/imageprocessing/dera/group_home.html
  DERA Computer Vision and Electro Optics Group point of contact:
  Dr. John Savage, jtsavage@dera.gov.uk, +44 1344 633203

  A UK patent has been granted: "Method for digitally processing
  images to determine the position of edges and/or corners therein for
  guidance of unmanned vehicle", UK Patent 2272285. Proprietor:
  Secretary of State for Defence, UK. 15 January 1997

  This code is issued for research purposes only and remains the
  property of the UK Secretary of State for Defence. This code must
  not be passed on without this header information being kept
  intact. This code must not be sold.

\**********************************************************************/

/* }}} */
/* {{{ Readme First */

/**********************************************************************\

  SUSAN Version 2l
  SUSAN = Smallest Univalue Segment Assimilating Nucleus

  Email:    steve@fmrib.ox.ac.uk
  WWW:      http://www.fmrib.ox.ac.uk/~steve

  Related paper:
  @article{Smith97,
        author = "Smith, S.M. and Brady, J.M.",
        title = "{SUSAN} - A New Approach to Low Level Image Processing",
        journal = "Int. Journal of Computer Vision",
        pages = "45--78",
        volume = "23",
        number = "1",
        month = "May",
        year = 1997}

  To be registered for automatic (bug) updates of SUSAN, send an email.

  Compile with:
  gcc -O4 -o susan susan2l.c -lm

  See following section for different machine information. Please
  report any bugs (and fixes). There are a few optional changes that
  can be made in the "defines" section which follows shortly.

  Usage: type "susan" to get usage. Only PGM format files can be input
  and output. Utilities such as the netpbm package and XV can be used
  to convert to and from other formats. Any size of image can be
  processed.

  This code is written using an emacs folding mode, making moving
  around the different sections very easy. This is why there are
  various marks within comments and why comments are indented.


  SUSAN QUICK:

  This version of the SUSAN corner finder does not do all the
  false-corner suppression and thus is faster and produced some false
  positives, particularly on strong edges. However, because there are
  less stages involving thresholds etc., the corners that are
  correctly reported are usually more stable than those reported with
  the full algorithm. Thus I recommend at least TRYING this algorithm
  for applications where stability is important, e.g., tracking.

  THRESHOLDS:

  There are two thresholds which can be set at run-time. These are the
  brightness threshold (t) and the distance threshold (d).

  SPATIAL CONTROL: d

  In SUSAN smoothing d controls the size of the Gaussian mask; its
  default is 4.0. Increasing d gives more smoothing. In edge finding,
  a fixed flat mask is used, either 37 pixels arranged in a "circle"
  (default), or a 3 by 3 mask which gives finer detail. In corner
  finding, only the larger 37 pixel mask is used; d is not
  variable. In smoothing, the flat 3 by 3 mask can be used instead of
  a larger Gaussian mask; this gives low smoothing and fast operation.

  BRIGHTNESS CONTROL: t

  In all three algorithms, t can be varied (default=20); this is the
  main threshold to be varied. It determines the maximum difference in
  greylevels between two pixels which allows them to be considered
  part of the same "region" in the image. Thus it can be reduced to
  give more edges or corners, i.e. to be more sensitive, and vice
  versa. In smoothing, reducing t gives less smoothing, and vice
  versa. Set t=10 for the test image available from the SUSAN web
  page.

  ITERATIONS:

  With SUSAN smoothing, more smoothing can also be obtained by
  iterating the algorithm several times. This has a different effect
  from varying d or t.

  FIXED MASKS:

  37 pixel mask:    ooo       3 by 3 mask:  ooo
                   ooooo                    ooo
                  ooooooo                   ooo
                  ooooooo
                  ooooooo
                   ooooo
                    ooo

  CORNER ATTRIBUTES dx, dy and I
  (Only read this if you are interested in the C implementation or in
  using corner attributes, e.g., for corner matching)

  Corners reported in the corner list have attributes associated with
  them as well as positions. This is useful, for example, when
  attempting to match corners from one image to another, as these
  attributes can often be fairly unchanged between images. The
  attributes are dx, dy and I. I is the value of image brightness at
  the position of the corner. In the case of susan_corners_quick, dx
  and dy are the first order derivatives (differentials) of the image
  brightness in the x and y directions respectively, at the position
  of the corner. In the case of normal susan corner finding, dx and dy
  are scaled versions of the position of the centre of gravity of the
  USAN with respect to the centre pixel (nucleus).

  BRIGHTNESS FUNCTION LUT IMPLEMENTATION:
  (Only read this if you are interested in the C implementation)

  The SUSAN brightness function is implemented as a LUT
  (Look-Up-Table) for speed. The resulting pointer-based code is a
  little hard to follow, so here is a brief explanation. In
  setup_brightness_lut() the LUT is setup. This mallocs enough space
  for *bp and then repositions the pointer to the centre of the
  malloced space. The SUSAN function e^-(x^6) or e^-(x^2) is
  calculated and converted to a uchar in the range 0-100, for all
  possible image brightness differences (including negative
  ones). Thus bp[23] is the output for a brightness difference of 23
  greylevels. In the SUSAN algorithms this LUT is used as follows:

  p=in + (i-3)*x_size + j - 1;
  p points to the first image pixel in the circular mask surrounding
  point (x,y).

  cp=bp + in[i*x_size+j];
  cp points to a position in the LUT corresponding to the brightness
  of the centre pixel (x,y).

  now for every pixel within the mask surrounding (x,y),
  n+=*(cp-*p++);
  the brightness difference function is found by moving the cp pointer
  down by an amount equal to the value of the pixel pointed to by p,
  thus subtracting the two brightness values and performing the
  exponential function. This value is added to n, the running USAN
  area.

  in SUSAN smoothing, the variable height mask is implemented by
  multiplying the above by the moving mask pointer, reset for each new
  centre pixel.
  tmp = *dpt++ * *(cp-brightness);

\**********************************************************************/

/* }}} */
/* {{{ Machine Information */

/**********************************************************************\

  Success has been reported with the following:

  MACHINE  OS         COMPILER

  Sun      4.1.4      bundled C, gcc

  Next

  SGI      IRIX       SGI cc

  DEC      Unix V3.2+ 

  IBM RISC AIX        gcc

  PC                  Borland 5.0

  PC       Linux      gcc-2.6.3

  PC       Win32      Visual C++ 4.0 (Console Application)

  PC       Win95      Visual C++ 5.0 (Console Application)
                      Thanks to Niu Yongsheng <niuysbit@163.net>:
                      Use the FOPENB option below

  PC       DOS        djgpp gnu C
                      Thanks to Mark Pettovello <mpettove@umdsun2.umd.umich.edu>:
                      Use the FOPENB option below

  HP       HP-UX      bundled cc
                      Thanks to Brian Dixon <briand@hpcvsgen.cv.hp.com>:
                      in ksh:
                      export CCOPTS="-Aa -D_HPUX_SOURCE | -lM"
                      cc -O3 -o susan susan2l.c

\**********************************************************************/

/* }}} */
/* {{{ History */

/**********************************************************************\

  SUSAN Version 2l, 12/2/99
  Changed GNUDOS option to FOPENB.
  (Thanks to Niu Yongsheng <niuysbit@163.net>.)
  Took out redundant "sq=sq/2;".

  SUSAN Version 2k, 19/8/98:
  In corner finding:
  Changed if(yy<sq) {...} else if(xx<sq) {...} to
          if(yy<xx) {...} else {...}
  (Thanks to adq@cim.mcgill.edu - Alain Domercq.)

  SUSAN Version 2j, 22/10/97:
  Fixed (mask_size>x_size) etc. tests in smoothing.
  Added a couple of free() calls for cgx and cgy.
  (Thanks to geoffb@ucs.ed.ac.uk - Geoff Browitt.)

  SUSAN Version 2i, 21/7/97:
  Added information about corner attributes.

  SUSAN Version 2h, 16/12/96:
  Added principle (initial enhancement) option.

  SUSAN Version 2g, 2/7/96:
  Minor superficial changes to code.

  SUSAN Version 2f, 16/1/96:
  Added GNUDOS option (now called FOPENB; see options below).

  SUSAN Version 2e, 9/1/96:
  Added -b option.
  Fixed 1 pixel horizontal offset error for drawing edges.

  SUSAN Version 2d, 27/11/95:
  Fixed loading of certain PGM files in get_image (again!)

  SUSAN Version 2c, 22/11/95:
  Fixed loading of certain PGM files in get_image.
  (Thanks to qu@San-Jose.ate.slb.com - Gongyuan Qu.)

  SUSAN Version 2b, 9/11/95:
  removed "z==" error in edges routines.

  SUSAN Version 2a, 6/11/95:
  Removed a few unnecessary variable declarations.
  Added different machine information.
  Changed "header" in get_image to char.

  SUSAN Version 2, 1/11/95: first combined version able to take any
  image sizes.

  SUSAN "Versions 1", circa 1992: the various SUSAN algorithms were
  developed during my doctorate within different programs and for
  fixed image sizes. The algorithms themselves are virtually unaltered
  between "versions 1" and the combined program, version 2.

\**********************************************************************/

/* }}} */
/* {{{ defines, includes and typedefs */

/* ********** Optional settings */
#include "susan.h"

/* }}} */
/* {{{ usage() */


/* }}} */
/* {{{ get_image(filename,in,x_size,y_size) */

/* {{{ int getint(fp) derived from XV */





/* }}} */
/* {{{ int_to_uchar(r,in,size) */

int_to_uchar(r,in,size)
  uchar *in;
  int   *r, size;
{
int i,
    max_r=r[0],
    min_r=r[0];

  for (i=0; i<size; i++)
    {
      if ( r[i] > max_r )
        max_r=r[i];
      if ( r[i] < min_r )
        min_r=r[i];
    }

  /*printf("min=%d max=%d\n",min_r,max_r);*/

  max_r-=min_r;

  for (i=0; i<size; i++)
    in[i] = (uchar)((int)((int)(r[i]-min_r)*255)/max_r);
}

/* }}} */
/* {{{ setup_brightness_lut(bp,thresh,form) */

void setup_brightness_lut(int thresh,int form)
{
int   k;
int temp;



  for(k=-256;k<257;k++)
  {
    temp=fpdiv(int_to_float(k),int_to_float(thresh));
    temp = fpmul(temp,temp);
    if (form==6)
      temp=fpmul(temp,fpmul(temp,temp));
    temp=fpmul( 0x42c80000 ,fp_Exp(fpsub(0,-temp)));
    *(bp+k+256)= (uchar)temp;
  }
}

/* }}} */





/* }}} */

/* }}} */
/* {{{ smoothing */

/* {{{ median(in,i,j,x_size) */

uchar median(in,i,j,x_size)
  uchar *in;
  int   i, j, x_size;
{
int p[8],k,l,tmp;

  p[0]=in[(i-1)*x_size+j-1];
  p[1]=in[(i-1)*x_size+j  ];
  p[2]=in[(i-1)*x_size+j+1];
  p[3]=in[(i  )*x_size+j-1];
  p[4]=in[(i  )*x_size+j+1];
  p[5]=in[(i+1)*x_size+j-1];
  p[6]=in[(i+1)*x_size+j  ];
  p[7]=in[(i+1)*x_size+j+1];

  for(k=0; k<7; k++)
    for(l=0; l<(7-k); l++)
      if (p[l]>p[l+1])
      {
        tmp=p[l]; p[l]=p[l+1]; p[l+1]=tmp;
      }

  return( (p[3]+p[4]) / 2 );
}

/* }}} */
/* {{{ enlarge(in,tmp_image,x_size,y_size,border) */

/* this enlarges "in" so that borders can be dealt with easily */

enlarge(x_size,y_size,border)
  int   *x_size, *y_size, border;
{
int   i, j;

  for(i=0; i<*x_size; i++){   /* copy *in into tmp_image */
        for(j=0; j<*y_size; j++)
    tmp_image[(i+border)*(*y_size+2*border)+border+j] =  dataIn[i* *y_size+j];//, *x_size;
  }

  for(i=0; i<border; i++){   /* copy top and bottumn into tmp_image */
        for(j=0; j<*y_size; j++){
          tmp_image[(border-i-1)*(*y_size+2*border)+border+j] =  dataIn[i* *y_size+j];//, *x_size;
          tmp_image[(border + *x_size + i)*(*y_size+2*border)+border+j] =  dataIn[(*x_size - i-1)* *y_size+j];//, *x_size;
        }

  }

  for(i=0; i<*x_size+2*border; i++){   /* copy left and right columns */
      for(j=0; j< border; j++){
          tmp_image[i*(*y_size+2*border)+border - 1 - j] =  tmp_image[i*(*y_size+2*border)+border + j];//, *x_size;
          tmp_image[i*(*y_size+2*border)+*y_size + border + j] =  tmp_image[i*(*y_size+2*border) + *y_size + border - 1 - j];//, *x_size;
      }

  }

  *x_size+=2*border;  /* alter image size */
  *y_size+=2*border;
}

/* }}} */
/* {{{ void susan_smoothing(three_by_three,in,dt,x_size,y_size,bp) */

void susan_smoothing(int three_by_three,unsigned int dt,int x_size,int y_size)
{
/* {{{ vars */

unsigned int temp;
int   n_max, increment, mask_size,
      i,j,x,y,area,brightness,tmp,centre;
uchar *ip, *dpt, *cp,*in;
      // tmp_image[9810];
TOTAL_TYPE total;

// Copy the original data to out array as uchar
for(i=0;i<7220;i++)
  out[i] = dataIn[i];

/* }}} */

  /* {{{ setup larger image and border sizes */


  mask_size = 7;

  total=0.1; /* test for total's type */

  if ( (2*mask_size+1>x_size) || (2*mask_size+1>y_size) )
  {
    // printf("Mask size (1.5*distance_thresh+1=%d) too big for image (%dx%d).\n",mask_size,x_size,y_size);
    exit(0);
  }

  enlarge(&x_size,&y_size,mask_size);

/* }}} */

       /* large Gaussian masks */
    /* {{{ setup distance lut */

  n_max = (mask_size*2) + 1;

  increment = x_size - n_max;

  dpt    = dp;
  temp   = fpsub(0,fpmul(dt,dt));
    int l=0;
  for(i=-mask_size; i<=mask_size; i++)
    for(j=-mask_size; j<=mask_size; j++)
    {
      x = fpmul( 0x42c80000 , fp_Exp( fpdiv(((i*i)+(j*j)) , temp )));
      x = cast_Fp_To_Int(x);
      *dpt++ = (unsigned char)x;
    }

// /* }}} */
//     /* {{{ main section */
  in  = tmp_image;
  for (i=mask_size;i<y_size-mask_size;i++)
  {
    for (j=mask_size;j<x_size-mask_size;j++)
    {
      area = 0;
      total = 0;
      dpt = dp;
      ip = in + ((i-mask_size)*x_size) + j - mask_size;
      centre = in[i*x_size+j];
      cp = bp + centre+256;
      for(y=-mask_size; y<=mask_size; y++)
      {
        for(x=-mask_size; x<=mask_size; x++)
	{
          brightness = *ip++;
          tmp = *dpt++ * *(cp-brightness);
          area += tmp;
          total += tmp * brightness;
        }
        ip += increment;
      }
      tmp = area-10000;
     
      if (tmp==0)
        out[l]=median(in,i,j,x_size);
      else
        out[l]=((total-(centre*10000))/tmp);
        l+=1;
    }
  }

// /* }}} */


// /* }}} */
//   }
}

/* }}} */

/* }}} */
/* {{{ edges */

/* {{{ edge_draw(in,corner_list,drawing_mode) */

edge_draw(in,mid,x_size,y_size,drawing_mode)
  uchar *in, *mid;
  int x_size, y_size, drawing_mode;
{
int   i;
uchar *inp, *midp;

  if (drawing_mode==0)
  {
    /* mark 3x3 white block around each edge point */
    midp=mid;
    for (i=0; i<x_size*y_size; i++)
    {
      if (*midp<8) 
      {
        inp = in + (midp - mid) - x_size - 1;
        *inp++=255; *inp++=255; *inp=255; inp+=x_size-2;
        *inp++=255; *inp++;     *inp=255; inp+=x_size-2;
        *inp++=255; *inp++=255; *inp=255;
      }
      midp++;
    }
  }

  /* now mark 1 black pixel at each edge point */
  midp=mid;
  for (i=0; i<x_size*y_size; i++)
  {
    if (*midp<8) 
      *(in + (midp - mid)) = 0;
    midp++;
  }
}

/* }}} */
/* {{{ susan_thin(r,mid,x_size,y_size) */

/* only one pass is needed as i,j are decremented if necessary to go
   back and do bits again */



/* }}} */
/* {{{ susan_edges(in,r,sf,max_no,out) */

susan_edges(in,r,mid,bp,max_no,x_size,y_size)
  uchar *in, *bp, *mid;
  int   *r, max_no, x_size, y_size;
{
int z,x_f,y_f;//float z
int   do_symmetry, i, j, m, n, a, b, x, y, w;
uchar c,*p,*cp;

  memset_Int_t (r,0,x_size * y_size);

  for (i=3;i<y_size-3;i++)
    for (j=3;j<x_size-3;j++)
    {
      n=100;
      p=in + (i-3)*x_size + j - 1;
      cp=bp + in[i*x_size+j];

      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p);
      p+=x_size-3; 

      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p);
      p+=x_size-5;

      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p);
      p+=x_size-6;

      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p);
      p+=2;
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p);
      p+=x_size-6;

      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p);
      p+=x_size-5;

      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p);
      p+=x_size-3;

      n+=*(cp-*p++);
      n+=*(cp-*p++);
      n+=*(cp-*p);

      if (n<=max_no)
        r[i*x_size+j] = max_no - n;
    }

  for (i=4;i<y_size-4;i++)
    for (j=4;j<x_size-4;j++)
    {
      if (r[i*x_size+j]>0)
      {
        m=r[i*x_size+j];
        n=max_no - m;
        cp=bp + in[i*x_size+j];

        if (n>600)
        {
          p=in + (i-3)*x_size + j - 1;
          x=0;y=0;

          c=*(cp-*p++);x-=c;y-=3*c;
          c=*(cp-*p++);y-=3*c;
          c=*(cp-*p);x+=c;y-=3*c;
          p+=x_size-3; 
    
          c=*(cp-*p++);x-=2*c;y-=2*c;
          c=*(cp-*p++);x-=c;y-=2*c;
          c=*(cp-*p++);y-=2*c;
          c=*(cp-*p++);x+=c;y-=2*c;
          c=*(cp-*p);x+=2*c;y-=2*c;
          p+=x_size-5;
    
          c=*(cp-*p++);x-=3*c;y-=c;
          c=*(cp-*p++);x-=2*c;y-=c;
          c=*(cp-*p++);x-=c;y-=c;
          c=*(cp-*p++);y-=c;
          c=*(cp-*p++);x+=c;y-=c;
          c=*(cp-*p++);x+=2*c;y-=c;
          c=*(cp-*p);x+=3*c;y-=c;
          p+=x_size-6;

          c=*(cp-*p++);x-=3*c;
          c=*(cp-*p++);x-=2*c;
          c=*(cp-*p);x-=c;
          p+=2;
          c=*(cp-*p++);x+=c;
          c=*(cp-*p++);x+=2*c;
          c=*(cp-*p);x+=3*c;
          p+=x_size-6;
    
          c=*(cp-*p++);x-=3*c;y+=c;
          c=*(cp-*p++);x-=2*c;y+=c;
          c=*(cp-*p++);x-=c;y+=c;
          c=*(cp-*p++);y+=c;
          c=*(cp-*p++);x+=c;y+=c;
          c=*(cp-*p++);x+=2*c;y+=c;
          c=*(cp-*p);x+=3*c;y+=c;
          p+=x_size-5;

          c=*(cp-*p++);x-=2*c;y+=2*c;
          c=*(cp-*p++);x-=c;y+=2*c;
          c=*(cp-*p++);y+=2*c;
          c=*(cp-*p++);x+=c;y+=2*c;
          c=*(cp-*p);x+=2*c;y+=2*c;
          p+=x_size-3;

          c=*(cp-*p++);x-=c;y+=3*c;
          c=*(cp-*p++);y+=3*c;
          c=*(cp-*p);x+=c;y+=3*c;
          x_f = int_to_float(x);
          y_f = int_to_float(y);
          z = fp_Sqrt(fpadd(fpmul(x_f,x_f) ,fpmul(y_f,y_f)));
          int n_f = int_to_float(n);
          if (fp_ExtractSign(fpsub(z, fpmul(0x3f666666,n_f)) ) ==0) /* 0.5 *///  if (z > (0.9*(float)n)) /* 0.5 */
	        {
            do_symmetry=0;
            if (x==0)
              z=0x49742400;//1000000.0
            else{
              x_f = int_to_float(x);
              y_f = int_to_float(y);
              z=fpmul(y_f,x_f);
            }
              
            if (fp_ExtractSign(z)) { z=fpsub(0,z); w=-1; }
            else w=1;
            if (fpsub(z,0x3f000000)) /*if (z < 0.5)*/
              { /* vert_edge */ a=0; b=1; }
            else { if (fpsub(0x40000000,z)) /*(z > 2.0)*/
              { /* hor_edge */ a=1; b=0; }
            else { /* diag_edge */ if (w>0) { a=1; b=1; }
                                   else { a=-1; b=1; }}}
            if ( (m > r[(i+a)*x_size+j+b]) && (m >= r[(i-a)*x_size+j-b]) &&
                 (m > r[(i+(2*a))*x_size+j+(2*b)]) && (m >= r[(i-(2*a))*x_size+j-(2*b)]) )
              mid[i*x_size+j] = 1;
          }
          else
            do_symmetry=1;
        }
        else 
          do_symmetry=1;

        if (do_symmetry==1)
	{ 
          p=in + (i-3)*x_size + j - 1;
          x=0; y=0; w=0;

          /*   |      \
               y  -x-  w
               |        \   */

          c=*(cp-*p++);x+=c;y+=9*c;w+=3*c;
          c=*(cp-*p++);y+=9*c;
          c=*(cp-*p);x+=c;y+=9*c;w-=3*c;
          p+=x_size-3; 
  
          c=*(cp-*p++);x+=4*c;y+=4*c;w+=4*c;
          c=*(cp-*p++);x+=c;y+=4*c;w+=2*c;
          c=*(cp-*p++);y+=4*c;
          c=*(cp-*p++);x+=c;y+=4*c;w-=2*c;
          c=*(cp-*p);x+=4*c;y+=4*c;w-=4*c;
          p+=x_size-5;
    
          c=*(cp-*p++);x+=9*c;y+=c;w+=3*c;
          c=*(cp-*p++);x+=4*c;y+=c;w+=2*c;
          c=*(cp-*p++);x+=c;y+=c;w+=c;
          c=*(cp-*p++);y+=c;
          c=*(cp-*p++);x+=c;y+=c;w-=c;
          c=*(cp-*p++);x+=4*c;y+=c;w-=2*c;
          c=*(cp-*p);x+=9*c;y+=c;w-=3*c;
          p+=x_size-6;

          c=*(cp-*p++);x+=9*c;
          c=*(cp-*p++);x+=4*c;
          c=*(cp-*p);x+=c;
          p+=2;
          c=*(cp-*p++);x+=c;
          c=*(cp-*p++);x+=4*c;
          c=*(cp-*p);x+=9*c;
          p+=x_size-6;
    
          c=*(cp-*p++);x+=9*c;y+=c;w-=3*c;
          c=*(cp-*p++);x+=4*c;y+=c;w-=2*c;
          c=*(cp-*p++);x+=c;y+=c;w-=c;
          c=*(cp-*p++);y+=c;
          c=*(cp-*p++);x+=c;y+=c;w+=c;
          c=*(cp-*p++);x+=4*c;y+=c;w+=2*c;
          c=*(cp-*p);x+=9*c;y+=c;w+=3*c;
          p+=x_size-5;
 
          c=*(cp-*p++);x+=4*c;y+=4*c;w-=4*c;
          c=*(cp-*p++);x+=c;y+=4*c;w-=2*c;
          c=*(cp-*p++);y+=4*c;
          c=*(cp-*p++);x+=c;y+=4*c;w+=2*c;
          c=*(cp-*p);x+=4*c;y+=4*c;w+=4*c;
          p+=x_size-3;

          c=*(cp-*p++);x+=c;y+=9*c;w-=3*c;
          c=*(cp-*p++);y+=9*c;
          c=*(cp-*p);x+=c;y+=9*c;w+=3*c;

          if (y==0)
            z = 0x49742400;//1000000.0;
          else{
              x_f = int_to_float(x);
              y_f = int_to_float(y);
              z = fpdiv(x_f,y_f);
          }

          if (fpsub(z,0x3f000000)) { /* vertical */ a=0; b=1; }
          else { if (fpsub(0x40000000,z))/*if(z>0.2)*/ { /* horizontal */ a=1; b=0; }
          else { /* diagonal */ if (w>0) { a=-1; b=1; }
                                else { a=1; b=1; }}}
          if ( (m > r[(i+a)*x_size+j+b]) && (m >= r[(i-a)*x_size+j-b]) &&
               (m > r[(i+(2*a))*x_size+j+(2*b)]) && (m >= r[(i-(2*a))*x_size+j-(2*b)]) )
            mid[i*x_size+j] = 2;	
        }
      }
    }
}

/* }}} */
/* {{{ susan_edges_small(in,r,sf,max_no,out) */



/* }}} */

/* }}} */
/* {{{ corners */

/* {{{ corner_draw(in,corner_list,drawing_mode) */

corner_draw(in,corner_list,x_size,drawing_mode)
  uchar *in;
  CORNER_LIST corner_list;
  int x_size, drawing_mode;
{
uchar *p;
int   n=0;

  while(corner_list[n].info != 7)
  {
    if (drawing_mode==0)
    {
      p = in + (corner_list[n].y-1)*x_size + corner_list[n].x - 1;
      *p++=255; *p++=255; *p=255; p+=x_size-2;
      *p++=255; *p++=0;   *p=255; p+=x_size-2;
      *p++=255; *p++=255; *p=255;
      n++;
    }
    else
    {
      p = in + corner_list[n].y*x_size + corner_list[n].x;
      *p=0;
      n++;
    }
  }
}

/* }}} */
/* {{{ susan(in,r,sf,max_no,corner_list) */

// susan_corners(in,r,bp,max_no,corner_list,x_size,y_size)
//   uchar       *in, *bp;
//   int         *r, max_no, x_size, y_size;
//   CORNER_LIST corner_list;
// {
// int   n,x,y,sq,xx,yy,
//       i,j,*cgx,*cgy;
// float divide;
// uchar c,*p,*cp;

//   memset (r,0,x_size * y_size * sizeof(int));

//   cgx=(int *)malloc(x_size*y_size*sizeof(int));
//   cgy=(int *)malloc(x_size*y_size*sizeof(int));

//   for (i=5;i<y_size-5;i++)
//     for (j=5;j<x_size-5;j++) {
//         n=100;
//         p=in + (i-3)*x_size + j - 1;
//         cp=bp + in[i*x_size+j];

//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p);
//         p+=x_size-3; 

//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p);
//         p+=x_size-5;

//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p);
//         p+=x_size-6;

//         n+=*(cp-*p++);
//         n+=*(cp-*p++);
//         n+=*(cp-*p);
//       if (n<max_no){    /* do this test early and often ONLY to save wasted computation */
//         p+=2;
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p);
//       if (n<max_no){
//         p+=x_size-6;

//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p);
//       if (n<max_no){
//         p+=x_size-5;

//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p);
//       if (n<max_no){
//         p+=x_size-3;

//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p++);
//       if (n<max_no){
//         n+=*(cp-*p);

//         if (n<max_no)
//         {
//             x=0;y=0;
//             p=in + (i-3)*x_size + j - 1;

//             c=*(cp-*p++);x-=c;y-=3*c;
//             c=*(cp-*p++);y-=3*c;
//             c=*(cp-*p);x+=c;y-=3*c;
//             p+=x_size-3; 
    
//             c=*(cp-*p++);x-=2*c;y-=2*c;
//             c=*(cp-*p++);x-=c;y-=2*c;
//             c=*(cp-*p++);y-=2*c;
//             c=*(cp-*p++);x+=c;y-=2*c;
//             c=*(cp-*p);x+=2*c;y-=2*c;
//             p+=x_size-5;
    
//             c=*(cp-*p++);x-=3*c;y-=c;
//             c=*(cp-*p++);x-=2*c;y-=c;
//             c=*(cp-*p++);x-=c;y-=c;
//             c=*(cp-*p++);y-=c;
//             c=*(cp-*p++);x+=c;y-=c;
//             c=*(cp-*p++);x+=2*c;y-=c;
//             c=*(cp-*p);x+=3*c;y-=c;
//             p+=x_size-6;

//             c=*(cp-*p++);x-=3*c;
//             c=*(cp-*p++);x-=2*c;
//             c=*(cp-*p);x-=c;
//             p+=2;
//             c=*(cp-*p++);x+=c;
//             c=*(cp-*p++);x+=2*c;
//             c=*(cp-*p);x+=3*c;
//             p+=x_size-6;
    
//             c=*(cp-*p++);x-=3*c;y+=c;
//             c=*(cp-*p++);x-=2*c;y+=c;
//             c=*(cp-*p++);x-=c;y+=c;
//             c=*(cp-*p++);y+=c;
//             c=*(cp-*p++);x+=c;y+=c;
//             c=*(cp-*p++);x+=2*c;y+=c;
//             c=*(cp-*p);x+=3*c;y+=c;
//             p+=x_size-5;

//             c=*(cp-*p++);x-=2*c;y+=2*c;
//             c=*(cp-*p++);x-=c;y+=2*c;
//             c=*(cp-*p++);y+=2*c;
//             c=*(cp-*p++);x+=c;y+=2*c;
//             c=*(cp-*p);x+=2*c;y+=2*c;
//             p+=x_size-3;

//             c=*(cp-*p++);x-=c;y+=3*c;
//             c=*(cp-*p++);y+=3*c;
//             c=*(cp-*p);x+=c;y+=3*c;

//             xx=x*x;
//             yy=y*y;
//             sq=xx+yy;
//             if ( sq > ((n*n)/2) )
//             {
//               if(yy<xx) {
//                 divide=(float)y/(float)abs(x);
//                 sq=abs(x)/x;
//                 sq=*(cp-in[(i+FTOI(divide))*x_size+j+sq]) +
//                    *(cp-in[(i+FTOI(2*divide))*x_size+j+2*sq]) +
//                    *(cp-in[(i+FTOI(3*divide))*x_size+j+3*sq]);}
//               else {
//                 divide=(float)x/(float)abs(y);
//                 sq=abs(y)/y;
//                 sq=*(cp-in[(i+sq)*x_size+j+FTOI(divide)]) +
//                    *(cp-in[(i+2*sq)*x_size+j+FTOI(2*divide)]) +
//                    *(cp-in[(i+3*sq)*x_size+j+FTOI(3*divide)]);}

//               if(sq>290){
//                 r[i*x_size+j] = max_no-n;
//                 cgx[i*x_size+j] = (51*x)/n;
//                 cgy[i*x_size+j] = (51*y)/n;}
//             }
// 	}
// }}}}}}}}}}}}}}}}}}}

//   /* to locate the local maxima */
//   n=0;
//   for (i=5;i<y_size-5;i++)
//     for (j=5;j<x_size-5;j++) {
//        x = r[i*x_size+j];
//        if (x>0)  {
//           /* 5x5 mask */
// #ifdef FIVE_SUPP
//           if (
//               (x>r[(i-1)*x_size+j+2]) &&
//               (x>r[(i  )*x_size+j+1]) &&
//               (x>r[(i  )*x_size+j+2]) &&
//               (x>r[(i+1)*x_size+j-1]) &&
//               (x>r[(i+1)*x_size+j  ]) &&
//               (x>r[(i+1)*x_size+j+1]) &&
//               (x>r[(i+1)*x_size+j+2]) &&
//               (x>r[(i+2)*x_size+j-2]) &&
//               (x>r[(i+2)*x_size+j-1]) &&
//               (x>r[(i+2)*x_size+j  ]) &&
//               (x>r[(i+2)*x_size+j+1]) &&
//               (x>r[(i+2)*x_size+j+2]) &&
//               (x>=r[(i-2)*x_size+j-2]) &&
//               (x>=r[(i-2)*x_size+j-1]) &&
//               (x>=r[(i-2)*x_size+j  ]) &&
//               (x>=r[(i-2)*x_size+j+1]) &&
//               (x>=r[(i-2)*x_size+j+2]) &&
//               (x>=r[(i-1)*x_size+j-2]) &&
//               (x>=r[(i-1)*x_size+j-1]) &&
// 	      (x>=r[(i-1)*x_size+j  ]) &&
// 	      (x>=r[(i-1)*x_size+j+1]) &&
// 	      (x>=r[(i  )*x_size+j-2]) &&
// 	      (x>=r[(i  )*x_size+j-1]) &&
// 	      (x>=r[(i+1)*x_size+j-2]) )
// #endif
// #ifdef SEVEN_SUPP
//           if ( 
//                 (x>r[(i-3)*x_size+j-3]) &&
//                 (x>r[(i-3)*x_size+j-2]) &&
//                 (x>r[(i-3)*x_size+j-1]) &&
//                 (x>r[(i-3)*x_size+j  ]) &&
//                 (x>r[(i-3)*x_size+j+1]) &&
//                 (x>r[(i-3)*x_size+j+2]) &&
//                 (x>r[(i-3)*x_size+j+3]) &&

//                 (x>r[(i-2)*x_size+j-3]) &&
//                 (x>r[(i-2)*x_size+j-2]) &&
//                 (x>r[(i-2)*x_size+j-1]) &&
//                 (x>r[(i-2)*x_size+j  ]) &&
//                 (x>r[(i-2)*x_size+j+1]) &&
//                 (x>r[(i-2)*x_size+j+2]) &&
//                 (x>r[(i-2)*x_size+j+3]) &&

//                 (x>r[(i-1)*x_size+j-3]) &&
//                 (x>r[(i-1)*x_size+j-2]) &&
//                 (x>r[(i-1)*x_size+j-1]) &&
//                 (x>r[(i-1)*x_size+j  ]) &&
//                 (x>r[(i-1)*x_size+j+1]) &&
//                 (x>r[(i-1)*x_size+j+2]) &&
//                 (x>r[(i-1)*x_size+j+3]) &&

//                 (x>r[(i)*x_size+j-3]) &&
//                 (x>r[(i)*x_size+j-2]) &&
//                 (x>r[(i)*x_size+j-1]) &&
//                 (x>=r[(i)*x_size+j+1]) &&
//                 (x>=r[(i)*x_size+j+2]) &&
//                 (x>=r[(i)*x_size+j+3]) &&

//                 (x>=r[(i+1)*x_size+j-3]) &&
//                 (x>=r[(i+1)*x_size+j-2]) &&
//                 (x>=r[(i+1)*x_size+j-1]) &&
//                 (x>=r[(i+1)*x_size+j  ]) &&
//                 (x>=r[(i+1)*x_size+j+1]) &&
//                 (x>=r[(i+1)*x_size+j+2]) &&
//                 (x>=r[(i+1)*x_size+j+3]) &&

//                 (x>=r[(i+2)*x_size+j-3]) &&
//                 (x>=r[(i+2)*x_size+j-2]) &&
//                 (x>=r[(i+2)*x_size+j-1]) &&
//                 (x>=r[(i+2)*x_size+j  ]) &&
//                 (x>=r[(i+2)*x_size+j+1]) &&
//                 (x>=r[(i+2)*x_size+j+2]) &&
//                 (x>=r[(i+2)*x_size+j+3]) &&

//                 (x>=r[(i+3)*x_size+j-3]) &&
//                 (x>=r[(i+3)*x_size+j-2]) &&
//                 (x>=r[(i+3)*x_size+j-1]) &&
//                 (x>=r[(i+3)*x_size+j  ]) &&
//                 (x>=r[(i+3)*x_size+j+1]) &&
//                 (x>=r[(i+3)*x_size+j+2]) &&
//                 (x>=r[(i+3)*x_size+j+3]) )
// #endif
// {
// corner_list[n].info=0;
// corner_list[n].x=j;
// corner_list[n].y=i;
// corner_list[n].dx=cgx[i*x_size+j];
// corner_list[n].dy=cgy[i*x_size+j];
// corner_list[n].I=in[i*x_size+j];
// n++;
// if(n==MAX_CORNERS){
//       fprintf(stderr,"Too many corners.\n");
//       exit(1);
//          }}}}
// corner_list[n].info=7;

// free(cgx);
// free(cgy);

// }

/* }}} */
/* {{{ susan_quick(in,r,sf,max_no,corner_list) */



/* }}} */

/* }}} */
/* {{{ main(argc, argv) */

int main(argc, argv)
  int   argc;
  char  *argv [];
{
/* {{{ vars */


char   *tcp;
uchar  *in;
unsigned int dt=0x40800000;//dt = 4.0
int    *r,
       argindex=3,
       bt=20,
       principle=0,
       thin_post_proc=1,
       three_by_three=0,
       drawing_mode=0,
       susan_quick=0,
       max_no_corners=1850,
       max_no_edges=2650,
       mode = 0, i,
       x_size, y_size;
CORNER_LIST corner_list;

/* }}} */





  /* {{{ look at options */


/* }}} */
  /* {{{ main processing */

  setup_brightness_lut(bt,2);
  susan_smoothing(three_by_three,dt,76,95);

//       /* {{{ edges */

      setup_brightness_lut(bt,6);

      
      memset_Char_t (mid,100,x_size * y_size); /* note not set to zero */


        susan_edges(in,r,mid,bp,max_no_edges,x_size,y_size);
    //   if(thin_post_proc)
        // susan_thin(r,mid,x_size,y_size);
      edge_draw(in,mid,x_size,y_size,drawing_mode);


// /* }}} */
//       /* {{{ corners */

      setup_brightness_lut(bt,6);


        //   susan_corners(in,r,bp,max_no_corners,corner_list,x_size,y_size);
        // corner_draw(in,corner_list,x_size,drawing_mode);



/* }}} */

//   put_image(argv[2],in,x_size,y_size);
  return 0;
}

/* }}} */
  // *in=tmp_image;      /* repoint in */error