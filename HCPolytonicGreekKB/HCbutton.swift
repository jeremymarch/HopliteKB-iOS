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
    
    var buttonDown:Bool = false
    let buttonTail:CGFloat = 4
    let buttonDownWidthFactor:CGFloat = 1.3
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
        
        backgroundColor = bgColor
        setTitleColor(textColor, for: [])
        
        self.addTarget(self, action: #selector(touchUpInside(sender:)), for: .touchUpInside)
        self.addTarget(self, action: #selector(touchUpOutside(sender:)), for: .touchUpOutside)
        self.addTarget(self, action: #selector(touchDown(sender:)), for: .touchDown)
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
            let width = self.frame.size.width / buttonDownWidthFactor
            let height = (self.frame.size.height - buttonTail) / buttonDownHeightFactor
            let x = self.frame.origin.x + ((self.frame.size.width - (self.frame.size.width / buttonDownWidthFactor)) / 2)
            let y = self.frame.origin.y + (self.frame.size.height - height - buttonTail)
            
            let buttonFrame = CGRect(x:x, y:y, width:width, height:height)
            self.frame = buttonFrame
            
            self.titleEdgeInsets = UIEdgeInsetsMake(0, 0, 0, 0);
            
            backgroundColor = bgColor
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
            let width = self.frame.size.width / buttonDownWidthFactor
            let height = (self.frame.size.height - buttonTail) / buttonDownHeightFactor
            let x = self.frame.origin.x + ((self.frame.size.width - (self.frame.size.width / buttonDownWidthFactor)) / 2)
            let y = self.frame.origin.y + (self.frame.size.height - height - buttonTail)
            
            let buttonFrame = CGRect(x:x, y:y, width:width, height:height)
            self.frame = buttonFrame
            
            self.titleEdgeInsets = UIEdgeInsetsMake(0, 0, 0, 0);
            
            backgroundColor = bgColor
            setTitleColor(textColor, for: [])
            setNeedsDisplay()
        }
    }
    
    func touchDown(sender: UIButton!) {
        buttonDown = true
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
            let width = self.frame.size.width * buttonDownWidthFactor
            let height = (self.frame.size.height * buttonDownHeightFactor) + buttonTail
            let x = self.frame.origin.x - (((self.frame.size.width * buttonDownWidthFactor) - self.frame.size.width) / 2)
            let y = self.frame.origin.y - height + self.frame.size.height + buttonTail
            
            let buttonFrame = CGRect(x:x, y:y, width:width, height:height)
            self.frame = buttonFrame
            
            self.titleEdgeInsets = UIEdgeInsetsMake(-50, 0, 0, 0);
            
            backgroundColor = bgDownColor
            setTitleColor(textDownColor, for: [])
            //self.superview?.bringSubview(toFront: self)
            setNeedsDisplay()
            
        }
        //setNeedsDisplay()
    }
    
    /*
     // Only override draw() if you perform custom drawing.
     // An empty implementation adversely affects performance during animation.
     override func draw(_ rect: CGRect) {
     // Drawing code
        let ctx = UIGraphicsGetCurrentContext()
     }
 */
    

}
