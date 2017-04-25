#include "FinalPro.h"


class Action
{
public:
	virtual void run() = 0;
	~Action(){}
};

class Resize : public Action
{
	public:
		virtual void run()
		{
			cout<<"ENTER THE WIDTH :: ";
		    cin>>w;
		    cout<<"\n";
		    cout<<"ENTER THE HEIGHT :: ";
		    cin>>h;
		    cout<<"\n";
		    cout<<"ENTER THE INPUT FILE NAME :: ";
		    cin>>Fname;
		    cout<<"\n";
		    cout<<"ENTER THE OUTPUT FILE NAME :: ";
		    cin>>OFname;

			int width = w;
  			int height = h;

            Mat original_img = imread(Fname);
  			Mat output_image_filename = imread(OFname);

  			if(!original_img.data ) 
  			{
    			cerr<<" Wrong file image";
    			return -1;
  			}

  			Mat cropped_img;

  			resize(original_img, cropped_img, Size(w, h));
  			imwrite(output_image_filename, cropped_img);

  			cout<<"Resized done";
		}
};

class dilate_errode : public Action
{
public:
	virtual void run()
	{
		Mat src, erosion_dst, dilation_dst;
		int erosion_type, dilation_type;

		int erosion_elem = 0;
		int erosion_size = 0;
		int dilation_elem = 0;
		int dilation_size = 0;
		int const max_elem = 2;
		int const max_kernel_size = 21;

		cout<<"ENTER THE INPUT FILE NAME :: ";
		cin>>Fname;

		src = imread(Fname);

		if( !src.data )
        { return -1; }

		namedWindow( "Dilation_Errode", CV_WINDOW_AUTOSIZE );


		createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",&erosion_elem, max_elem, Erosion );

        createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo", &erosion_size, max_kernel_size, Erosion );

  
        createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo", &dilation_elem, max_elem, Dilation );

        createTrackbar( "Kernel size:\n 2n +1", "Dilation Demo", &dilation_size, max_kernel_size, Dilation );

        if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  		else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  		else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  		Mat element = getStructuringElement( erosion_type, Size( 2*erosion_size + 1, 2*erosion_size+1 ), Point( erosion_size, erosion_size ) );

  		erode( src, erosion_dst, element );
  		imshow( "Erosion Demo", erosion_dst );


  		if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  		else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  		else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  		Mat element = getStructuringElement( dilation_type, Size( 2*dilation_size + 1, 2*dilation_size+1 ), Point( dilation_size, dilation_size ) );

  		dilate( src, dilation_dst, element );
  		imshow( "Dilation Demo", dilation_dst );
  	}
};

class light_dark : public Action
{
public:
	virtual void run()
	{
		
	}
};

class panorama_stitch : public Action
{
public:
	virtual void run()
	{
		
	}
};



int main(int argc, const char** argv)
{
	cout<<"_____________IMAGE EDITOR_____________\n\n";
	cout<<"SELECT FROM THE FOLLOWING OPTIONS:\n";
	cout<<"1: RESIZING\n";
	cout<<"2: DILATION / EROSION\n";
	cout<<"3: LIGHTEN / DARKEN \n";
	cout<<"2: PANORAMA / STITCHING \n";
	cout<<"\n\n";
	cin>>result;
    Action *action;
	switch(result)
	{
		case 1: 
		      action = new resize();
		      break;

		case 2:
		      action = new dilate_errode();
		      break;

		case 3:
		      action = new light_dark();
		      break;

		case 4:
		      action = new panorama_stitch();
		      break;

		default: cout<<"WRONG INPUT\n";
	}
  return 0;

}

