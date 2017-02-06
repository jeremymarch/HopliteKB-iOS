//
//  HCbutton.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 1/14/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCButton: UIButton {

    var btype: Int? = nil
    /*
    var bgColor:UIColor = .white
    var bgDownColor:UIColor = .black
    var textColor:UIColor = .black
    var textDownColor:UIColor = .white
    */
    
    var bgColor = HopliteConstants.keyBGColor
    var textColor = HopliteConstants.keyTextColor
    var bgDownColor = HopliteConstants.keyBGColorDown
    var textDownColor = HopliteConstants.keyTextColorDown
    
    let buttonRadius:CGFloat = 4.0
    
    let fontSize:CGFloat = 24.0
    let downFontSize:CGFloat = 36.0
    var buttonDown:Bool = false
    let buttonTail:CGFloat = 4
    let buttonDownWidthFactor:CGFloat = 1.46
    let buttonDownHeightFactor:CGFloat = 2.26
    let hPadding:CGFloat = 3;
    let vPadding:CGFloat = 8;
    let topMargin:CGFloat = 4;
    let buttonDownAddHeight:CGFloat = 62;
    
    let blueColor:UIColor = UIColor.init(red: 0/255.0, green: 122/255.0, blue: 255/255.0, alpha: 1.0)
    
    required init(buttonType: Int = 0) {
        // set myValue before super.init is called
        self.btype = buttonType
        
        super.init(frame: .zero)
        
        // set other operations after super.init, if required
        
        //backgroundColor = bgColor
        setTitleColor(textColor, for: [])
        backgroundColor = UIColor.clear
        self.titleLabel!.font = UIFont(name: self.titleLabel!.font.fontName, size: fontSize)
        
        self.addTarget(self, action: #selector(self.touchUpInside(sender:)), for: .touchUpInside)
        self.addTarget(self, action: #selector(self.touchUpOutside(sender:)), for: .touchUpOutside)
        self.addTarget(self, action: #selector(self.touchDown(sender:)), for: .touchDown)
        
        //these don't work, maybe this:
        //http://stackoverflow.com/questions/31916979/how-touch-drag-enter-works
        //self.addTarget(self, action: #selector(touchDown(sender:)), for: .touchDragEnter)
        //self.addTarget(self, action: #selector(touchUpOutside(sender:)), for: .touchDragExit)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func touchUpInside(sender: UIButton!) {
        buttonDown = false
        
        if self.titleLabel?.text == "enter"
        {
            setTitleColor(.white, for: [])
            backgroundColor = blueColor
        }
        else if self.titleLabel?.text == "space"
        {
            setTitleColor(.gray, for: [])
            backgroundColor = .white
        }
        else
        {
            if !(self.frame.size.width > self.frame.size.height * 1.5) && UIDevice.current.userInterfaceIdiom == .phone
            {
            let width = self.frame.size.width / buttonDownWidthFactor
            let height = (self.frame.size.height - buttonTail) / buttonDownHeightFactor
            let x = self.frame.origin.x + ((self.frame.size.width - (self.frame.size.width / buttonDownWidthFactor)) / 2)
            let y = self.frame.origin.y + (self.frame.size.height - height - buttonTail)
            
            let buttonFrame = CGRect(x:x, y:y, width:width, height:height)
            self.frame = buttonFrame
            self.titleLabel!.font = UIFont(name: self.titleLabel!.font.fontName, size: fontSize)
            self.titleEdgeInsets = UIEdgeInsetsMake(0, 0, 0, 0);
            }
            setTitleColor(textColor, for: [])
            setNeedsDisplay()
        }
    }
    
    func touchUpOutside(sender: UIButton!) {
        buttonDown = false
        if self.titleLabel?.text == "enter"
        {
            setTitleColor(.white, for: [])
            backgroundColor = blueColor
        }
        else if self.titleLabel?.text == "space"
        {
            setTitleColor(.gray, for: [])
            backgroundColor = .white
        }
        else
        {
            if !(self.frame.size.width > self.frame.size.height * 1.5) && UIDevice.current.userInterfaceIdiom == .phone
            {
            let width = self.frame.size.width / buttonDownWidthFactor
            let height = (self.frame.size.height - buttonTail) / buttonDownHeightFactor
            let x = self.frame.origin.x + ((self.frame.size.width - (self.frame.size.width / buttonDownWidthFactor)) / 2)
            let y = self.frame.origin.y + (self.frame.size.height - height - buttonTail)
            
            let buttonFrame = CGRect(x:x, y:y, width:width, height:height)
            self.frame = buttonFrame
            
            self.titleEdgeInsets = UIEdgeInsetsMake(0, 0, 0, 0);
            self.titleLabel!.font = UIFont(name: self.titleLabel!.font.fontName, size: fontSize)
            }
            setTitleColor(textColor, for: [])
            
            setNeedsDisplay()
        }
    }
    
    func touchDown(sender: UIButton!) {
        buttonDown = true
        //self.superview!.bringSubview(toFront: self)
        if self.titleLabel?.text == "enter"
        {
            setTitleColor(blueColor, for: [])
            backgroundColor = .white
        }
        else if self.titleLabel?.text == "space"
        {
            setTitleColor(.white, for: [])
            backgroundColor = .black
        }
        else
        {
            if !(self.frame.size.width > self.frame.size.height * 1.5) && UIDevice.current.userInterfaceIdiom == .phone
            {
                let width = self.frame.size.width * buttonDownWidthFactor
                let height = (self.frame.size.height * buttonDownHeightFactor) + buttonTail
                let x = self.frame.origin.x - (((self.frame.size.width * buttonDownWidthFactor) - self.frame.size.width) / 2)
                let y = self.frame.origin.y - height + self.frame.size.height + buttonTail
                
                let buttonFrame = CGRect(x:x, y:y, width:width, height:height)
                self.frame = buttonFrame
                
                self.titleEdgeInsets = UIEdgeInsetsMake(-50, 0, 0, 0);
                self.titleLabel!.font = UIFont(name: self.titleLabel!.font.fontName, size: downFontSize)
                setTitleColor(textColor, for: [])
            }
            else
            {
                setTitleColor(textDownColor, for: [])
            }
            setNeedsDisplay()
        }
    }
        
     // Only override draw() if you perform custom drawing.
     // An empty implementation adversely affects performance during animation.
     override func draw(_ rect: CGRect) {
        //NSLog("drawdraw: \(rect.size.width), \(rect.size.height)")
        
        let depressedPhoneButton:Bool = (buttonDown && !(rect.size.width > rect.size.height * 1.5)) && UIDevice.current.userInterfaceIdiom == .phone
        
        let ctx = UIGraphicsGetCurrentContext()
        
        let outerRect:CGRect = self.bounds//.insetBy(dx: 4.0, dy: 4.0);
     
        var outerPath:CGPath
        if depressedPhoneButton
        {
            outerPath = createDepressedButtonForRect(rect: outerRect, radius: buttonRadius + 2);
        }
        else
        {
            if UIDevice.current.userInterfaceIdiom == .pad
            {
                outerPath = UIBezierPath(roundedRect: outerRect, cornerRadius: HopliteConstants.ipadRadius).cgPath
            }
            else
            {
                outerPath = UIBezierPath(roundedRect: outerRect, cornerRadius: HopliteConstants.normalRadius).cgPath
        
            }
        }
        ctx?.saveGState()
        ctx?.addPath(outerPath)
        ctx?.clip()
        ctx?.restoreGState()

        ctx?.saveGState()
        ctx?.addPath(outerPath)
        if depressedPhoneButton
        {
            ctx?.setFillColor(bgColor.cgColor)
        }
        else if buttonDown
        {
            ctx?.setFillColor(bgDownColor.cgColor)
        }
        else
        {
            ctx?.setFillColor(bgColor.cgColor)
        }
        ctx?.fillPath()
        ctx?.restoreGState()
        
        if depressedPhoneButton
        {
            ctx?.saveGState()
            ctx?.addPath(outerPath)
            ctx?.setStrokeColor(UIColor.lightGray.cgColor)
            ctx?.strokePath()
            ctx?.restoreGState()
        }
    }
 
    func createDepressedButtonForRect(rect:CGRect, radius:CGFloat ) -> CGMutablePath
    {
        let inset:CGFloat = 8
        let topHeight:CGFloat = rect.size.height / 2
        let midHeight:CGFloat = rect.size.height / 4
    
        let path:CGMutablePath = CGMutablePath()
        path.move(to: CGPoint(x: rect.midX, y: rect.minY))
        
        //NE
        path.addArc(tangent1End: CGPoint(x:rect.maxX, y:rect.minY), tangent2End: CGPoint(x:rect.maxX, y:rect.maxY), radius: radius)
        
        path.addLine(to: CGPoint(x:rect.maxX, y:rect.minY + topHeight))
        path.addLine(to: CGPoint(x:rect.maxX - inset, y:rect.minY + topHeight + midHeight))
        
        //SE
        path.addArc(tangent1End: CGPoint(x:rect.maxX - inset, y:rect.maxY), tangent2End: CGPoint(x:rect.minX - inset, y:rect.maxY), radius: radius)
        //SW
        path.addArc(tangent1End: CGPoint(x:rect.minX + inset, y:rect.maxY), tangent2End: CGPoint(x:rect.minX, y:rect.minY), radius: radius)

        path.addLine(to: CGPoint(x:rect.minX + inset, y: rect.minY + topHeight + midHeight))
        path.addLine(to: CGPoint(x:rect.minX, y:rect.minY + topHeight))

        //NW
        path.addArc(tangent1End: CGPoint(x:rect.minX, y:rect.minY), tangent2End: CGPoint(x:rect.maxX, y:rect.minY), radius: radius)
    
        path.closeSubpath()
    
        return path;
    }

}
