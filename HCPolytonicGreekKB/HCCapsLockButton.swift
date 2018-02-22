//
//  HCCapsLockButton.swift
//  HCPolytonicGreekKBapp
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Created by Jeremy March on 1/19/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCCapsLockButton: UIButton {

    var buttonDown:Bool = false
    var capsLockOn:Bool = false
    
    var lineColor1:UIColor           = HopliteConstants.otherTextColor
    var bgColor1:UIColor        = HopliteConstants.otherBGColor
    var lineColorDown:UIColor            = HopliteConstants.otherTextColorDown
    var bgColorDown:UIColor       = HopliteConstants.otherBGColorDown
    
    required init() {
        super.init(frame: .zero)
        
        self.addTarget(self, action: #selector(touchUpInside1(sender:)), for: .touchUpInside)
        self.addTarget(self, action: #selector(touchUpOutside1(sender:)), for: .touchUpOutside)
        self.addTarget(self, action: #selector(touchDown1(sender:)), for: .touchDown)
        
        self.addTarget(self, action: #selector(touchDown1(sender:)), for: .touchDragEnter)
        self.addTarget(self, action: #selector(touchUpInside1(sender:)), for: .touchDragExit)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    @objc func touchUpInside1(sender: UIButton!) {
        capsLockOn = !capsLockOn
        buttonDown = false
        setNeedsDisplay()
    }
    
    @objc func touchUpOutside1(sender: UIButton!) {
        
        buttonDown = false
        setNeedsDisplay()
    }
    
    @objc func touchDown1(sender: UIButton!) {
        
        buttonDown = true
        setNeedsDisplay()
    }
    
    func radians(_ degrees:Double) -> Double
    {
        return degrees * Double.pi/180;
    }
    
    func resetToLower()
    {
        capsLockOn = false
        setNeedsDisplay()
    }
    
    override func draw(_ rect: CGRect) {
        // Drawing code
        
        let outerRect:CGRect = self.bounds.insetBy(dx: 0, dy: 0);
        let buttonRadius:CGFloat
        if UIDevice.current.userInterfaceIdiom == .pad
        {
            buttonRadius = HopliteConstants.ipadRadius
        }
        else
        {
            buttonRadius = HopliteConstants.normalRadius
        }
        let outerPath:CGPath = UIBezierPath(roundedRect: outerRect, cornerRadius: buttonRadius).cgPath
        
        let ctx = UIGraphicsGetCurrentContext()
        ctx!.addPath(outerPath)
        if buttonDown
        {
            ctx!.setFillColor(bgColorDown.cgColor)
        }
        else
        {
            ctx!.setFillColor(bgColor1.cgColor)
        }
        ctx?.fillPath()
        
        
        let bHeight = self.bounds.size.height
        let bWidth = self.bounds.size.width
        
        let stemWidth = bHeight * 0.28
        let hang = stemWidth / 2
        let stemHeight = bHeight / 5
        let arrowHeight = stemHeight * 1.5
        let topPadding:CGFloat = (bHeight - stemHeight - arrowHeight) / 2
        let sidePadding:CGFloat = (bWidth - (hang * 2) - stemWidth) / 2
        
        let path:CGMutablePath = CGMutablePath()
        
        path.move(to: CGPoint(x: sidePadding + hang, y: topPadding + arrowHeight + stemHeight))
        path.addLine(to: CGPoint(x:sidePadding + hang, y:topPadding + arrowHeight)) //to top of stem
        path.addLine(to: CGPoint(x:sidePadding, y:topPadding + arrowHeight)) //to hang
        path.addLine(to: CGPoint(x:bWidth / 2, y:topPadding)) //to point
        path.addLine(to: CGPoint(x:sidePadding + (hang * 2) + stemWidth, y:topPadding + arrowHeight)) //to right hang
        path.addLine(to: CGPoint(x:sidePadding + hang + stemWidth, y:topPadding + arrowHeight)) //to stem
        path.addLine(to: CGPoint(x:sidePadding + hang + stemWidth, y:topPadding + arrowHeight + stemHeight)) //to bottom of stem
        path.closeSubpath() //back to start
        
        ctx!.addPath(path);
        
        if capsLockOn
        {
            if buttonDown
            {
                ctx!.setFillColor(lineColorDown.cgColor)
            }
            else
            {
                ctx!.setFillColor(lineColor1.cgColor)
            }
            ctx!.fillPath()
            ctx!.setLineWidth(1.5)
            ctx!.strokePath()
        }
        else
        {
            if buttonDown
            {
                ctx!.setStrokeColor(lineColorDown.cgColor)
            }
            else
            {
                ctx!.setStrokeColor(lineColor1.cgColor)
            }
            ctx!.setLineWidth(1.5)
            ctx!.strokePath()
        }
    }
}
