//
//  HCCapsLockButton.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 1/19/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCCapsLockButton: UIButton {

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
        
        
        let padding = 4.0
        let hang = 2.0
        //let stemWidth = rect.size.width - padding * 2


    }
    
    func drawX(context:CGContext, rect1:CGRect, offset:CGFloat, color:CGColor)
    {
        var rect:CGRect = rect1
        //center and make the rect square
        if rect.size.width > rect.size.height
        {
            rect.origin.x += (rect.size.width - rect.size.height) / 2;
            rect.size.width = rect.size.height;
        }
        else
        {
            rect.origin.y += (rect.size.height - rect.size.width) / 2;
            rect.size.height = rect.size.width;
        }
        
        context.saveGState();
        context.setLineWidth(2.5);
        context.setStrokeColor(color);
        context.move(to: CGPoint(x:rect.minX + offset, y: rect.minY + offset))
        context.addLine(to: CGPoint(x:rect.maxX - offset, y:rect.maxY - offset))
        context.move(to: CGPoint(x:rect.maxX - offset, y:rect.minY + offset))
        context.addLine(to: CGPoint(x:rect.minX + offset, y:rect.maxY - offset))
        context.strokePath();
        context.restoreGState();
    }

}
