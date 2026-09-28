//
//  BusteniApp.swift
//  Busteni
//
//  Created by Adrian Poplesanu on 28.09.2026.
//

import SwiftUI

@main
struct BusteniApp: App {

    @State private var metrics = MetricsStore()

    var body: some Scene {
        MenuBarExtra {
            ContentView()
        } label: {
            Text(metrics.menuBarTitle)
                .monospacedDigit()
        }
        .menuBarExtraStyle(.window)
    }
}
