//
//  ViewController.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 12/24/16.
//  Copyright © 2016 Jeremy March. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet var textView:UITextView?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //these 3 lines prevent undo/redo/paste from displaying above keyboard on ipad
        if #available(iOS 9.0, *)
        {
            let item : UITextInputAssistantItem = textView!.inputAssistantItem
            item.leadingBarButtonGroups = []
            item.trailingBarButtonGroups = []
        }
        
        
        //to include keyboard in app
        /*
        let k = KeyboardViewController()
        k.view.autoresizingMask = [.flexibleWidth, .flexibleHeight] //this works to set height
        textView!.inputView = k.view
        */
        //this works to set height
        //k.view.frame = CGRect(x:0 , y:0, width:self.view.frame.width, height:k.portraitHeight)
        
        /* 
        //these do not work to set height
         let heightConstraint = NSLayoutConstraint(item: k.view,
         attribute: .height,
         relatedBy: .equal,
         toItem: nil,
         attribute: .notAnAttribute,
         multiplier: 1.0,
         constant: k.portraitHeight)
         heightConstraint.priority = 999.0
         heightConstraint.isActive = true
         
         //self.inputView!.addConstraint(heightConstraint)
        //these don't work
        //k.view.heightAnchor.constraint(equalToConstant: k.portraitHeight)
        //k.view.widthAnchor.constraint(equalToConstant: self.view.frame.width)
        */
        
 
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}
