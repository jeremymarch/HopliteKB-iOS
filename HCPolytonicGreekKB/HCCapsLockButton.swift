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
    var capsLockOn:Bool = false
    
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
        capsLockOn = !capsLockOn
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
        
        let bWidth = self.bounds.size.width
        let bHeight = self.bounds.size.height
        let stemWidth = bWidth / 3
        let hang = stemWidth / 2
        let stemHeight = bHeight / 5
        let arrowHeight = stemHeight * 1.4
        let topPadding:CGFloat = (bHeight - stemHeight - arrowHeight) / 2
        let sidePadding:CGFloat = (bWidth - (hang * 2) - stemWidth) / 2
        
        let path:CGMutablePath = CGMutablePath()
        
        path.move(to: CGPoint(x: sidePadding + hang, y: topPadding + arrowHeight + stemHeight))
        path.addLine(to: CGPoint(x:sidePadding + hang, y:topPadding + arrowHeight)) //to top of stem
        path.addLine(to: CGPoint(x:sidePadding, y:topPadding + arrowHeight)) //to hang
        path.addLine(to: CGPoint(x:bWidth / 2, y:topPadding)) //to point
        path.addLine(to: CGPoint(x:bWidth - sidePadding, y:topPadding + arrowHeight)) //to right hang
        path.addLine(to: CGPoint(x:bWidth - sidePadding - hang, y:topPadding + arrowHeight)) //to stem
        path.addLine(to: CGPoint(x:bWidth - sidePadding - hang, y:topPadding + arrowHeight + stemHeight)) //to bottom of stem
        path.closeSubpath() //back to start
        
        ctx!.addPath(path);
        
        if capsLockOn
        {
            ctx!.setFillColor(UIColor.black.cgColor)
            ctx!.fillPath()
        }
        else
        {
            ctx!.strokePath()
        }
    }
}
