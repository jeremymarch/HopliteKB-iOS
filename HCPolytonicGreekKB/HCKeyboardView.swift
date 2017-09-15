//
//  HCKeyboardView.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 9/14/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCKeyboardView: UIView {
    var buttons:[[UIButton]] = []
    /*
    // Only override draw() if you perform custom drawing.
    // An empty implementation adversely affects performance during animation.
    override func draw(_ rect: CGRect) {
        // Drawing code
    }
    */
    override func layoutSubviews() {
        let viewWidth:CGFloat = self.bounds.width
        let viewHeight:CGFloat = self.bounds.height

        var maxColumns = buttons[0].count
        for a in buttons[0]
        {
            if a.titleLabel?.text == "xxx"
            {
                maxColumns -= 1
            }
        }
        let maxRows = buttons.count
        var buttonSpacing:CGFloat = 5.0
        if maxColumns > 9
        {
            buttonSpacing = 4.0
        }
        let buttonWidth = (viewWidth - (buttonSpacing * (CGFloat(maxColumns) + 1.0))) / CGFloat(maxColumns)
        let buttonHeight = (viewHeight - (buttonSpacing * (CGFloat(maxRows) + 1.0))) / CGFloat(maxRows)
        
        var c = 0
        var xoffstart:CGFloat = 0
        var xoff:CGFloat = 0
        
        for (i, row) in buttons.enumerated()
        {
            c = row.count
            xoffstart = 0
            xoff = 0
            
            if c < maxColumns
            {
                xoffstart = ((buttonWidth + buttonSpacing) / 2.0) * CGFloat(maxColumns - c) + buttonSpacing
            }
            else
            {
                xoffstart = buttonSpacing
            }
            xoff = xoffstart
            var x = false //skip one
            for a in row {
                if a.titleLabel?.text == "enter" || a.titleLabel?.text == "space"
                {
                    if !x
                    {
                        x = true
                        continue
                    }
                    xoff -= (buttonWidth * 2.6) - buttonWidth
                }
            }
            for (j, key) in row.enumerated()
            {
                if key.titleLabel?.text == "xxx"
                {
                    key.isHidden = true
                }
                else
                {
                    key.isHidden = false
                    if i == 3 && j == 7
                    {
                        key.frame = CGRect(x: xoff, y: (CGFloat(i) * (buttonSpacing + buttonHeight)) + buttonSpacing, width: buttonWidth * 1.36, height: buttonHeight)
                        xoff += buttonSpacing + (buttonWidth * 1.36)
                    }
                    else if key.titleLabel?.text == "enter" || key.titleLabel?.text == "space"
                    {
                        key.frame = CGRect(x: xoff, y: (CGFloat(i) * (buttonSpacing + buttonHeight)) + buttonSpacing, width: buttonWidth * 2.6, height: buttonHeight)
                        xoff += buttonSpacing + (buttonWidth * 2.6)
                    }
                    else
                    {
                        //let aa = key as! HCButton
                        var buttonDown = false
                        if let aa = key as? HCButton
                        {
                            if aa.buttonDown
                            {
                                buttonDown = true
                            }
                        }
                        
                        if buttonDown
                        {
                            let aa = key as! HCButton
                            let width2 = buttonWidth * aa.buttonDownWidthFactor
                            let height2 = (buttonHeight * aa.buttonDownHeightFactor) + aa.buttonTail
                            let x2 = xoff - (((buttonWidth * aa.buttonDownWidthFactor) - buttonWidth) / 2)
                            let y2 = ((CGFloat(i) * (buttonSpacing + buttonHeight)) + buttonSpacing) - height2 + buttonHeight + aa.buttonTail
                            
                            key.frame = CGRect(x: x2, y: y2, width: width2, height: height2)
                            key.superview?.bringSubview(toFront: key)
                            xoff += (buttonSpacing + buttonWidth)
                        }
                        else
                        {
                            key.frame = CGRect(x: xoff, y: (CGFloat(i) * (buttonSpacing + buttonHeight)) + buttonSpacing, width: buttonWidth, height: buttonHeight)
                            xoff += (buttonSpacing + buttonWidth)
                        }
                    }
                }
                
            }
        }
    }
}
