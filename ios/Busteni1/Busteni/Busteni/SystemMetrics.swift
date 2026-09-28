//
//  SystemMetrics.swift
//  Busteni
//
//  Created by Adrian Poplesanu on 28.09.2026.
//

import Foundation
import Darwin.Mach

struct MemoryMetrics {
    let total: UInt64
    let active: UInt64
    let inactive: UInt64
    let wired: UInt64
    let compressed: UInt64
    let free: UInt64
    let speculative: UInt64
    let purgeable: UInt64
    /// Anonymous (non-file-backed) resident memory.
    let anonymous: UInt64
    /// File-backed resident memory (cache; mostly reclaimable).
    let fileBacked: UInt64

    /// RAM that counts toward pressure: anonymous + compressor, minus purgeable.
    /// File cache (`fileBacked`) is excluded because macOS can drop it freely.
    var pressureUsed: UInt64 {
        let raw = anonymous + compressed

        if raw > purgeable {
            return raw - purgeable
        }

        return 0
    }

    /// Memory pressure as a percentage: `pressureUsed / total * 100`.
    var pressurePercent: Double {
        guard total > 0 else {
            return 0
        }

        let pressure =
            Double(pressureUsed) / Double(total) * 100.0

        return min(100.0, max(0.0, pressure))
    }
}

struct CPUStats {
    let usage: Double
}

struct SystemMetrics {

    // MARK: - Memory

    static func totalMemory() -> UInt64 {
        ProcessInfo.processInfo.physicalMemory
    }

    static func memoryMetrics() -> MemoryMetrics? {

        var statistics = vm_statistics64()

        var count = mach_msg_type_number_t(
            MemoryLayout<vm_statistics64_data_t>.size
                / MemoryLayout<integer_t>.size
        )

        let result = withUnsafeMutablePointer(to: &statistics) {
            $0.withMemoryRebound(
                to: integer_t.self,
                capacity: Int(count)
            ) {
                host_statistics64(
                    mach_host_self(),
                    HOST_VM_INFO64,
                    $0,
                    &count
                )
            }
        }

        guard result == KERN_SUCCESS else {
            return nil
        }

        let pageSize = UInt64(vm_kernel_page_size)

        let active = UInt64(statistics.active_count) * pageSize
        let inactive = UInt64(statistics.inactive_count) * pageSize
        let wired = UInt64(statistics.wire_count) * pageSize
        let compressed = UInt64(statistics.compressor_page_count) * pageSize
        let free = UInt64(statistics.free_count) * pageSize
        let speculative = UInt64(statistics.speculative_count) * pageSize
        let purgeable = UInt64(statistics.purgeable_count) * pageSize
        let anonymous = UInt64(statistics.internal_page_count) * pageSize
        let fileBacked = UInt64(statistics.external_page_count) * pageSize

        return MemoryMetrics(
            total: totalMemory(),
            active: active,
            inactive: inactive,
            wired: wired,
            compressed: compressed,
            free: free,
            speculative: speculative,
            purgeable: purgeable,
            anonymous: anonymous,
            fileBacked: fileBacked
        )
    }


    // MARK: - CPU

    private static var previousUser: UInt64 = 0
    private static var previousSystem: UInt64 = 0
    private static var previousIdle: UInt64 = 0
    private static var previousNice: UInt64 = 0

    static func cpuUsage() -> CPUStats? {

        var cpuInfo: processor_info_array_t?
        var numCPUInfo: mach_msg_type_number_t = 0
        var numCPUs: natural_t = 0

        let result = host_processor_info(
            mach_host_self(),
            PROCESSOR_CPU_LOAD_INFO,
            &numCPUs,
            &cpuInfo,
            &numCPUInfo
        )

        guard result == KERN_SUCCESS, let cpuInfo else {
            return nil
        }

        defer {
            let size =
                vm_size_t(numCPUInfo)
                * vm_size_t(MemoryLayout<integer_t>.size)

            vm_deallocate(
                mach_task_self_,
                vm_address_t(bitPattern: cpuInfo),
                size
            )
        }

        var user: UInt64 = 0
        var system: UInt64 = 0
        var idle: UInt64 = 0
        var nice: UInt64 = 0

        for cpu in 0..<Int(numCPUs) {

            let offset = cpu * Int(CPU_STATE_MAX)

            user += UInt64(
                cpuInfo[offset + Int(CPU_STATE_USER)]
            )

            system += UInt64(
                cpuInfo[offset + Int(CPU_STATE_SYSTEM)]
            )

            idle += UInt64(
                cpuInfo[offset + Int(CPU_STATE_IDLE)]
            )

            nice += UInt64(
                cpuInfo[offset + Int(CPU_STATE_NICE)]
            )
        }

        let totalPrevious =
            previousUser
            + previousSystem
            + previousIdle
            + previousNice

        let totalCurrent =
            user
            + system
            + idle
            + nice

        let totalDelta = totalCurrent - totalPrevious
        let idleDelta = idle - previousIdle

        previousUser = user
        previousSystem = system
        previousIdle = idle
        previousNice = nice

        guard totalDelta > 0 else {
            return nil
        }

        let usage =
            1.0 - (Double(idleDelta) / Double(totalDelta))

        return CPUStats(
            usage: usage * 100.0
        )
    }
}
