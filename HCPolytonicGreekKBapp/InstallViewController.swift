//
//  InstallViewController.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 2/23/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//


import UIKit

class InstallViewController: UIViewController {
@IBOutlet var label:UILabel?
    override func viewDidLoad() {
        super.viewDidLoad()
        label?.sizeToFit()
        

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    override func viewWillAppear(_ animated: Bool) {
        //[[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
        self.navigationController?.setNavigationBarHidden(false, animated: true)
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
