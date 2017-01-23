//
//  HCGlobeButton.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 1/18/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCGlobeButton: UIButton {
    
    var buttonPressed:Bool = false
    
    required init() {
        super.init(frame: .zero)
        
        self.addTarget(self, action: #selector(touchUpInside1(sender:)), for: .touchUpInside)
        self.addTarget(self, action: #selector(touchUpOutside1(sender:)), for: .touchUpOutside)
        self.addTarget(self, action: #selector(touchDown1(sender:)), for: .touchDown)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func touchUpInside1(sender: UIButton!) {
        
        buttonPressed = false
        setNeedsDisplay()
    }
    
    func touchUpOutside1(sender: UIButton!) {
        
        buttonPressed = false
        setNeedsDisplay()
    }
    
    func touchDown1(sender: UIButton!) {
        
        buttonPressed = true
        setNeedsDisplay()
    }
    
    func radians(_ degrees:Double) -> Double
    {
        return degrees * M_PI/180;
    }
    
    override func draw(_ rect: CGRect) {
        
        let ctx = UIGraphicsGetCurrentContext()
        
        var lineColor:CGColor?
        var bgColor:CGColor?
        if buttonPressed
        {
            lineColor = UIColor.white.cgColor
            bgColor = UIColor.black.cgColor
        }
        else
        {
            lineColor = UIColor.black.cgColor
            bgColor = UIColor.white.cgColor
        }
        
        // Draw background
        let outerRect:CGRect = self.bounds.insetBy(dx: 0, dy: 0);
        let outerPath:CGPath = UIBezierPath(roundedRect: outerRect, cornerRadius: 4.0).cgPath
        ctx!.addPath(outerPath)
        ctx!.setFillColor(bgColor!)
        ctx?.fillPath()
        
        let min:CGFloat
        if self.frame.size.width > self.frame.size.height
        {
            min = self.frame.size.height
        }
        else
        {
            min = self.frame.size.width
        }
        let center = CGPoint(x:self.frame.size.width / 2.0, y:self.frame.size.height / 2.0)
        
        var vCenter = CGPoint(x:self.frame.size.width / 2.0, y:self.frame.size.height / 2.0)
        
        ctx!.beginPath()
        ctx!.setLineWidth(1.5)
        ctx!.setStrokeColor(lineColor!)
        
        let radius:CGFloat = min / 3.0
        let endAngle: CGFloat = CGFloat(2 * M_PI)

        //circle
        ctx!.addArc(center: center, radius: radius, startAngle: 0.0, endAngle: endAngle, clockwise: true)
        ctx!.strokePath()
        
        //clip everything outside the circle
        ctx!.addArc(center: center, radius: radius, startAngle: 0.0, endAngle: endAngle, clockwise: true)
        ctx!.clip()
        
        //left arc
        vCenter = CGPoint(x:center.x + (radius/0.73), y:center.y)
        ctx!.addArc(center: vCenter, radius: radius + (radius/1.2), startAngle: 0.0, endAngle: endAngle, clockwise: true)
        ctx!.strokePath()
        
        //right arc
        vCenter = CGPoint(x:center.x - (radius/0.73), y:center.y)
        ctx!.addArc(center: vCenter, radius: radius + (radius/1.2), startAngle: 0.0, endAngle: endAngle, clockwise: true)
        ctx!.strokePath()
        
        //bottom arc
        vCenter = CGPoint(x:center.x, y:center.y + (radius*2.29))
        ctx!.addArc(center: vCenter, radius: radius + (radius/1.2), startAngle: 0.0, endAngle: endAngle, clockwise: true)
        ctx!.strokePath()
        
        //top arc
        vCenter = CGPoint(x:center.x, y:center.y - (radius*2.29))
        ctx!.addArc(center: vCenter, radius: radius + (radius/1.2), startAngle: 0.0, endAngle: endAngle, clockwise: true)
        ctx!.strokePath()
 
        //horizontal line
        ctx!.move(to: CGPoint(x:0, y:self.frame.size.height / 2.0))
        ctx!.addLine(to: CGPoint(x:self.frame.size.width, y: self.frame.size.height / 2.0))
        ctx!.strokePath()
        
        //vertical line
        ctx!.move(to: CGPoint(x:self.frame.size.width / 2.0, y:0))
        ctx!.addLine(to: CGPoint(x:self.frame.size.width / 2.0, y: self.frame.size.height))
        ctx!.strokePath()
    }
}
