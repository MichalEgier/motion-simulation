package main;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Polygon;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Locale;
import java.util.Scanner;

import javax.sound.sampled.Line;
import javax.swing.JComponent;
import javax.swing.JFrame;

class MyCanvas extends JComponent {
    
	int a = 50;
    int b = 50;
    
    int vx2 = 100;
    int vy2 = 200;
    
    int fx2 = 100;
    int fy2 = 200;
    
    public void setProps(int a, int b, int vx2, int vy2, int fx2, int fy2) {
        this.a=a; this.b=b;
        this.vx2 = vx2; this.vy2 = vy2;
        this.fx2 = fx2; this.fy2 = fy2;
        repaint();//mark this component to be repainted
    }
   
    public void paint(Graphics g) {
    	Graphics2D g2d = (Graphics2D) g;
    	super.paint(g);
    	g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,		//wygladzanie krawedzi
               RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.fillOval(a, b, 26, 26);
      //  Line line = new Line(a+25,b+25,c,d);
        g2d.drawLine(a+13, b+13, vx2, vy2);
        g2d.drawLine(a+13, b+13, fx2, fy2);
        
        //ARROW HEAD
        
        Polygon arrowHead = new Polygon();
        arrowHead.addPoint(0,5);
    	arrowHead.addPoint( -5, -5);
    	arrowHead.addPoint( 5,-5);
        
    	Polygon arrowHead2 = new Polygon();
        arrowHead2.addPoint(0,5);
    	arrowHead2.addPoint( -5, -5);
    	arrowHead2.addPoint( 5,-5);
    	
    	AffineTransform tx = new AffineTransform();
        tx.setToIdentity();
	    double angle = Math.atan2(vy2-b, vx2-a);
	    tx.translate(vx2, vy2);
	    tx.rotate((angle-Math.PI/2d));  

	    Graphics2D g2d2 = (Graphics2D) g2d.create();
	    g2d2.setTransform(tx);   
	    g2d2.fill(arrowHead);
	//    g2d2.dispose();
	    
	    AffineTransform tx2 = new AffineTransform();
        tx2.setToIdentity();
	    double angle2 = Math.atan2(fy2-b, fx2-a);
	    tx2.translate(fx2, fy2);
	    tx2.rotate((angle2-Math.PI/2d));  

	   // Graphics2D g2d2 = (Graphics2D) g2d.create();
	    g2d2.setTransform(tx2);   
	    g2d2.fill(arrowHead);
	    g2d2.dispose();
        
    }

  static public void main(String args[]){
    JFrame window = new JFrame();
    //window.setSize(1000,1000);
    window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    window.setBounds(30, 30, 1000, 1000);
  //  window.setBo
    MyCanvas canvas=new MyCanvas();
 //   canvas.setProps(20,40);
    window.getContentPane().add(canvas);
    window.setVisible(true);
    
    //===============================================
     
    FileReader fr = null;
    Scanner scanner = null;
    
    try {
    	
    	File file = new File("./file.txt");
    
    	fr = new FileReader(file);
    	
    	scanner = new Scanner(fr);
    	
    	scanner.useLocale(Locale.US);
    	
    	while(scanner.hasNext()) {
    		
    		String fx_str = scanner.nextLine();
    		System.out.println(fx_str);
    		double fx = Double.parseDouble(fx_str);
    				
    		String fy_str = scanner.nextLine();
    		System.out.println(fy_str);
    		double fy = Double.parseDouble(fy_str);
    		
    		String fz_str = scanner.nextLine();
    		double fz = Double.parseDouble(fz_str);
    		
    		String vx_str = scanner.nextLine();
    		double vx = Double.parseDouble(vx_str);
    		
    		String vy_str = scanner.nextLine();
    		double vy = Double.parseDouble(vy_str);
    		
    		String vz_str = scanner.nextLine();
    		double vz = Double.parseDouble(vz_str);
    		
    		String rx_str = scanner.nextLine();
    		System.out.println(rx_str);
    		double rx = Double.parseDouble(rx_str);
    		System.out.println(rx);
    		
    		String ry_str = scanner.nextLine();
    		System.out.println(ry_str);
    		double ry = Double.parseDouble(ry_str);
    		
    		String rz_str = scanner.nextLine();
    		double rz = Double.parseDouble(rz_str);
    		System.out.println("rx =" + rx);
    		System.out.println("ry =" + ry);

    		System.out.println("vx =" + vx);
    		System.out.println("vy =" + vy);
    		System.out.println("fx =" + fx);
    		System.out.println("fy =" + fy);
    		
    		canvas.setProps((int)(rx*100 + 50), (int)(ry*100 + 50),
    							(int)((int)(rx*100 + 63) + vx*1),
    							(int)((int)(ry*100 + 63) + vy*1),
    							(int)((int)(rx*100 + 63) + fx*0.1),
    							(int)((int)(ry*100 + 63) + fy*0.1));
    		Thread.sleep(5);
    	}
    	
    }
    catch(Exception e) {
    	e.printStackTrace();
    }
    finally {
    	
    	try {
    	if(scanner != null) scanner.close();
    	if(fr != null) fr.close();
    	}
    	catch(IOException e) {
    		e.printStackTrace();
    	}
    	
    }
    
  }
}
