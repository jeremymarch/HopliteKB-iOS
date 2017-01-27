//
//  HCDeleteButton.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 1/14/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCDeleteButton: UIButton {
    var device:Int?
    var buttonPressed:Bool = false
    
    required init(devicea:Int = 1) {
        let device = 1
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
    
    override func draw(_ rect: CGRect) {
        self.device = 1
        // Drawing code
        
        let buttonLight = UIColor.init(red: 229/255.0, green: 230/255.0, blue: 233/255.0, alpha: 1.0).cgColor
        let delIconColor = UIColor.init(red: 110/255.0, green: 110/255.0, blue: 128/255.0, alpha: 1.0)
        var xColor:CGColor?
        //let buttonDark = UIColor.init(red: 203/255.0, green: 204/255.0, blue: 210/255.0, alpha: 1.0).cgColor
        //let buttonDownLight = UIColor.init(red: 145/255.0, green: 145/255.0, blue: 160/255.0, alpha: 1.0)
        //let buttonDown = UIColor.init(red: 130/255.0, green: 130/255.0, blue: 147/255.0, alpha: 1.0)
        //let delIconColorLight = UIColor.init(red: 120/255.0, green: 120/255.0, blue: 138/255.0, alpha: 1.0)

        NSLog("Draw")
        let context = UIGraphicsGetCurrentContext()
        
        let buttonRadius:CGFloat = 4.0
        let outerSideMargin:CGFloat = 0.0//2.75
        let outerTopMargin:CGFloat = 0.0//5.0
        
        let outerRect:CGRect = self.bounds.insetBy(dx: outerSideMargin, dy: outerTopMargin);
        
        var outerPath:CGPath?
        if self.device == 1
        {
            outerPath = UIBezierPath(roundedRect: outerRect, cornerRadius: buttonRadius).cgPath
        }
        else
        {
            outerPath = UIBezierPath(roundedRect: outerRect, cornerRadius: buttonRadius).cgPath
        }
        //add bottom shadow

        if buttonPressed == true
        {
            //context!.saveGState()
            context!.addPath(outerPath!)
            context!.setFillColor(UIColor.white.cgColor)
            /*
            if self.device == 1
            {
                context!.setFillColor(UIColor.black.cgColor);
            }
            else if self.device == 2
            {
                context!.setFillColor(delIconColor.cgColor);
            }
            */
            context?.fillPath()
            //context!.restoreGState()
        }
        else
        {
            //Down state
            // Draw gradient for outer path
            
            //context!.saveGState()
            context!.addPath(outerPath!)
            context!.setFillColor(delIconColor.cgColor)
            /*
            if self.device == 1
            {
                context!.setFillColor(UIColor.red.cgColor);
            }
            else if self.device == 2
            {
                context!.setFillColor(delIconColor.cgColor);
            }
 */
            context?.fillPath()
            //context!.restoreGState()
        }
        
        //Draw delete button icon
        context!.saveGState();
        //if (self.device == IPAD)
        //    CGContextSetShadowWithColor(context, CGSizeMake(0, 1), 1.0, [UIColor whiteColor].CGColor);
        let delHeight:CGFloat = self.bounds.size.height;
        let delWidth:CGFloat = self.bounds.size.width;
        var topPadding:CGFloat?
        //var sidePadding:CGFloat?
        var xIconPadding:CGFloat?
        if self.device == 2
        {
            topPadding = self.bounds.size.height / 2.8;
            //sidePadding = self.bounds.size.width / 3.0;
            xIconPadding = self.bounds.size.width / 15.5;//6.0f;
        }
        else
        {
            topPadding = self.bounds.size.height / 5.0;
            //sidePadding = self.bounds.size.width / 5.0;
            xIconPadding = 4.0;
        }
        //NSLog(@"H: %f, W: %f", self.bounds.size.height, self.bounds.size.width);
        
        let delRadius:CGFloat = 2.0
        //let startX:CGFloat = ((delWidth + (1 * sidePadding!)) * 1 / 3) - 1
        
        let path:CGMutablePath = CGMutablePath()
        
        let iconWidth = delHeight * 0.75
        let iconPointWidth = iconWidth / 3
        let iconBodyWidth = iconWidth - iconPointWidth
        let delSidePadding = (delWidth - iconWidth) / 2
        
        
        path.move(to: CGPoint(x: delSidePadding + iconPointWidth, y: topPadding!)) //NW
        
        path.addArc(tangent1End: CGPoint(x: delWidth - delSidePadding, y: topPadding!), tangent2End: CGPoint(x: delWidth - delSidePadding, y:delHeight - topPadding!), radius: delRadius)
        path.addArc(tangent1End: CGPoint(x: delWidth - delSidePadding, y:delHeight - topPadding!), tangent2End: CGPoint(x: delSidePadding + iconPointWidth, y:delHeight - topPadding!), radius: delRadius)
        path.addLine(to: CGPoint(x:delSidePadding + iconPointWidth, y:delHeight - topPadding!))
        path.addLine(to: CGPoint(x:delSidePadding, y:delHeight / 2.0))
        
        
        path.closeSubpath();
        
        context!.addPath(path);
        var iconColor:CGColor?
        if self.device == 2
        {
            if buttonPressed
            {
                iconColor = buttonLight;
                xColor = delIconColor.cgColor;
            }
            else
            {
                iconColor = delIconColor.cgColor;
                xColor = buttonLight;
                
            }
        }
        else
        {
            if buttonPressed
            {
                iconColor = delIconColor.cgColor;
                xColor = buttonLight;
            }
            else
            {
                iconColor = buttonLight;
                xColor = delIconColor.cgColor;
            }
        }
        context!.setFillColor(iconColor!)
        context?.fillPath()
        context!.restoreGState()
        
        context!.saveGState();
        let xFrame:CGRect = CGRect(x:delSidePadding + iconPointWidth,y:topPadding!,width:iconBodyWidth, height:delHeight - (topPadding! * 2))
        
        drawX(context:context!, rect1:xFrame, offset:xIconPadding!, color:xColor!);
        
        context!.restoreGState();
 
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
