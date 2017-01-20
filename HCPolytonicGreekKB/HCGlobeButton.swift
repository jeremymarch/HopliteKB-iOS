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
        // Drawing code
        
        let outerRect:CGRect = self.bounds.insetBy(dx: 0, dy: 0);
        let outerPath:CGPath = UIBezierPath(roundedRect: outerRect, cornerRadius: 4.0).cgPath
        
        let ctx = UIGraphicsGetCurrentContext()
        ctx!.addPath(outerPath)
        ctx!.setFillColor(UIColor.white.cgColor)
        ctx?.fillPath()
        
        let min:CGFloat
        if self.frame.size.width > self.frame.size.height
        {
            min = self.frame.size.height
        }
        else /* mri 212-312-5179 */
        {
            min = self.frame.size.width
        }
        let center = CGPoint(x:self.frame.size.width / 2.0, y:self.frame.size.height / 2.0)
        
        ctx!.beginPath()
        
        //6
        ctx!.setLineWidth(1.5)
        
        //let x:CGFloat = center.x
        //let y:CGFloat = center.y
        let radius:CGFloat = min / 3.0
        let endAngle: CGFloat = CGFloat(2 * M_PI)
        
        //CGContextAddArc(ctx, x, y, radius, 0, endAngle, 0)
        ctx!.addArc(center: center, radius: radius, startAngle: 0.0, endAngle: endAngle, clockwise: true)
        ctx!.strokePath()
        
        ctx!.addArc(center: center, radius: radius/2, startAngle: 1.5, endAngle: 19.5, clockwise: true)
        ctx!.strokePath()
        
    }

}
